#!/usr/bin/env perl

#
# This script relies on nvram.h, nvram_defatauls.h and the \$(TOOLCHAIN_PREFIX)/.conf
# which are generated as make rules in the hostTools/Makefile
# we need to generate the nvram*.h files because Convert::Binary::C can't parse out
# createimg.c as there are some keywords like typedef, extern "C" which the module
# cannot parse
# \$(TOOLCHAIN_PREFIX).config contains information about the target cpu such as
# endinessnes, size of an integer etc
# Script initializes NVRAM_DATA structure and fills in values depending on the input parameters
# Dfault values will be used, e.g. flash block size, psi size etc for those which are not
# passed through command line argument
# To add a new NVRAM_DATA member,
# 1. Add entry in the arg_mapper hash (look at other examples)
# 2. Add entry to createimg_convert_binary.c as for_script_<new variable> = <#define>
# 3. Add parsing entry to pre_defs hash


use Convert::Binary::C;
use bytes;
use Getopt::Long;

use warnings;
use strict;




use Digest::CRC;

my $inputfile="";
my $outputfile="";
my $wholeflashfile="";
my $psi_size=24;
my $nvramfile="nvram.h";
my $nvram_defs_file="nvram_defaults.h";
my $configfile="";


#psisize=48 flblksz=16 auxfsprcnt= gponsn= gponpw= misc1=0 
my $arg_mapper = {
    'misc1' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'part_info'}[0]{'size'}=$val},
    'misc2' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'part_info'}[1]{'size'}=$val},
    'misc3' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'part_info'}[2]{'size'}=$val},
    'misc4' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'part_info'}[3]{'size'}=$val},
    'boardid' => sub { my $dstruct=shift, my $val=shift; $dstruct->{'szBoardId'}=$val; },
    'voiceboardid' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'szVoiceBoardId'}=$val; },
    'numbermac' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'ulNumMacAddrs'}=$val; },
    'macaddr'=>  sub { my $dstruct=shift; my $val=shift; $val=~ s/://g; ;$dstruct->{'ucaBaseMacAddr'}=pack('H*', $val); },
    'tp' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'ulMainTpNum'}=$val; },
    'psisize' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'ulPsiSize'}=$val; $psi_size=$val+0;},
    'flblksz' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'ucFlashBlkSize'}=$val; $psi_size=$val+0;},
    'logsize' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'ulSyslogSize'}=$val; },
    'auxfsprcnt' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'ucAuxFSPercent'}=$val; },
    'gponsn' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'gponSerialNumber'}=$val; },
    'backupPsi' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'backupPsi'}=$val;$psi_size=$val+0;},
    'gponpw' => sub { my $dstruct=shift; my $val=shift; $dstruct->{'gponPassword'}=$val; },
#    'inputfile' => sub { my $dstruct=shift; my $val=shift; $inputfile=$val; },
#    'outputfile' => sub { my $dstruct=shift; my $val=shift; $outputfile=$val; },
	
};


my (@alloptions);

Getopt::Long::Configure("no_ignore_case", "prefix_pattern=(--|-|\/)");
GetOptions ("inputfile=s" => \$inputfile,
	"outputfile=s" => \$outputfile,
	"wholeflashfile=s" => \$wholeflashfile,
	"config=s" => \$configfile,
	"set=s{,}" => \@alloptions,
	"nvramfile=s" => \$nvramfile,
	"nvramdefsfile=s" => \$nvram_defs_file);



if (! $configfile eq "" )
{
	require $configfile;
}




my $c = Convert::Binary::C->new(%main::config)->parse_file($nvramfile);
$c->tag('NVRAM_DATA.szBootline', Format=> 'String');
$c->tag('NVRAM_DATA.szBoardId', Format=> 'String');
$c->tag('NVRAM_DATA.szVoiceBoardId', Format=> 'String');
$c->tag('NVRAM_DATA.gponSerialNumber', Format=> 'String');
$c->tag('NVRAM_DATA.gponPassword', Format=> 'String');
$c->tag('NVRAM_DATA.ucaBaseMacAddr', Format=> 'Binary');


#these are the default values but we should read them from nvram_defaults.h
my $image_base=0xbfc00000;
my $ulNvramOffset=0x00000580;
my $numOfMac = 10;
my $tpNum = 0;
my $logSize= 0;
my $backupPsi = 0;
my $flashBlkSize = 64;
my $auxFSPercent = 0;
my $pmc_flag_bit=1;
my $token_len=20;

my $pre_defs = {
       'image_base' => sub { my $val=shift; $image_base=eval($val);},
        'nvram_offset' => sub { my $val=shift; $ulNvramOffset=eval($val);},
        'numOfMac' => sub { my $val=shift;  $numOfMac=eval($val);},
        'tpNum' => sub { my $val=shift;     $tpNum=eval($val);},
        'psiSize' => sub { my $val=shift;   $psi_size=eval($val);},
        'logSize' => sub { my $val=shift;   $logSize=eval($val);},
        'backupPsi' => sub { my $val=shift; $backupPsi=eval($val);},
        'auxFSPerc' => sub { my $val=shift; $auxFSPercent=eval($val);},
        'token_len' => sub { my $val=shift; $token_len=eval($val);},
        'pmc_flag_bit' => sub { my $val=shift; $pmc_flag_bit=eval($val);},
};

open nvdefines_file, $nvram_defs_file;

my @defs=<nvdefines_file>;

foreach(@defs) {
	my @lines=split(/=/, $_);

	if ($lines[0] =~m/.*for_script_.*/) {
		my $var=$lines[0];
		my $value=$lines[1];
		$var=~s/.*for_script_//;
		$value=~s/;.*//;
		my $fp=$pre_defs->{$var};
		if(ref($fp))
		{
			$fp->($value);
		}
	} 
	
} 


close nvdefines_file;

#initialize the data structure
my $ulNvramLen=$c->sizeof('NVRAM_DATA');
my $data= "\377" x $ulNvramLen;
my $dstruct=$c->unpack('NVRAM_DATA', $data);
$dstruct->{'szVoiceBoardId'}="\000";
#$dstruct->{'szBootline'}="\000";

#go through the command line arguments
#createimg --set boardid=963138REF_P502 voiceboardid=  numbermac=11 macaddr=02:10:18:01:00:01 tp=0 psisize=48 logsize= auxfsprcnt= gponsn= gponpw= inputfile=bcm963138BGWV_cfe_fs_kernel outputfile=bcm963138BGWV_flash_image_963138REF_P502
#
#

#set defaults
$dstruct->{'ulCheckSum'}=0;
$dstruct->{'ulVersion'}=6;
$dstruct->{'ulPsiSize'}=$psi_size;
$dstruct->{'backupPsi'}=$backupPsi;
$dstruct->{'ulSyslogSize'}=$logSize;
$dstruct->{'ucFlashBlkSize'}=$flashBlkSize;


    foreach (@alloptions) {
		my $carg=$_;
		my @pair=split(/=/, $carg);
		my $arg=$pair[0];
		$arg=~s/^--//;
		my $fp=$arg_mapper->{$arg};
		if(ref($fp))
		{
			$fp->($dstruct, $pair[1]);
		}
		else
		{
			if(exists($dstruct->{$arg}))
			{
				$dstruct->{$arg}=$pair[1];
			}
		}

        }
my $binary = $c->pack('NVRAM_DATA', $dstruct);
my $ctx = new Digest::CRC(width => 32, poly => 0x04c11db7, init => 0xffffffff, xorout => 0, refin => 1, refout => 1);
$ctx->add($binary);
my $csum=$ctx->digest;


$dstruct->{'ulCheckSum'}=$csum;
my $nvram_binary = $c->pack('NVRAM_DATA', $dstruct);

open temp_filefd, "> n.bin";
print temp_filefd $nvram_binary;
close(temp_filefd);


if ( $wholeflashfile eq "" )
{
	#we reached to a point where we read the input file tag
	#genearte outputbuffer
	#

	open ifile_fd, "< $inputfile" or die "Failed to open inputfile $inputfile\n";
	binmode ifile_fd;

	my $file_tag_len=$c->sizeof('FILE_TAG');

	# host is always little endian and we want to parse that accordingly
	my $c_ptag = Convert::Binary::C->new(%main::config)->parse_file($nvramfile);
	$c_ptag->tag('FILE_TAG.kernelAddress', Format=> 'String');
	$c_ptag->tag('FILE_TAG.kernelLen', Format=> 'String');
	$c_ptag->tag('FILE_TAG.boardId', Format=> 'String');
	$c_ptag->tag('FILE_TAG.totalImageLen', Format=> 'String');
	$c_ptag->tag('FILE_TAG.imageVersion', Format=> 'String');
	$c_ptag->tag('FILE_TAG.cfeAddress', Format=> 'String');
	$c_ptag->tag('FILE_TAG.cfeLen', Format=> 'String');
	$c_ptag->tag('FILE_TAG.rootfsAddress', Format=> 'String');
	$c_ptag->tag('FILE_TAG.rootfsLen', Format=> 'String');
	$c_ptag->tag('FILE_TAG.tagValidationToken', Format=> 'Binary');

	my $ptag;
	my $ptag_struct;

	if ( read (ifile_fd, $ptag, $file_tag_len) == $file_tag_len)
	{
		$ptag_struct=$c_ptag->unpack('FILE_TAG', $ptag);
	}

	my $ptag_1 = substr($ptag, 0, ($file_tag_len - $token_len));
	my $Ctx = new Digest::CRC(width => 32, poly => 0x04c11db7, init => 0xffffffff, xorout => 0, refin => 1, refout => 1);
	$Ctx->add($ptag_1);
	my $tvt=0;
	$tvt=$ptag_struct->{'tagValidationToken'} or die "Illegal image ! Tag crc failed.(tagValidationToken)\n";
	my $calc_csum=$Ctx->digest;
	my $regular_csum=0xfefe;
	$regular_csum=unpack("I", $tvt);
	my $reverse_csum=0xefef;
	$reverse_csum=unpack("N", $tvt);

	if ($calc_csum != $regular_csum)
	{
		if($calc_csum != $reverse_csum)
		{
			die("Illegal image ! Tag crc failed.\n");
		}
	}

	my $kaa=$ptag_struct->{'kernelAddress'} or die "Illegal image ! Tag crc failed.(kernelAddress)\n";
	my $ulKernelOffset=$kaa-$image_base;
	$kaa=$ptag_struct->{'kernelLen'} or die "Illegal image ! Tag crc failed.(kernelLen)\n";
	my $ulKernelLen=$kaa+0;
	$kaa=$ptag_struct->{'cfeAddress'} or die "Illegal image ! Tag crc failed.(cfeAddress)\n";
	my $ulCfeOffset=$kaa-$image_base;
	$kaa=$ptag_struct->{'cfeLen'} or die "Illegal image ! Tag crc failed.(cfeLen)\n";
	my $ulCfeLen=$kaa+0;
	$kaa=$ptag_struct->{'rootfsAddress'} or die "Illegal image ! Tag crc failed.(rootfsAddress)\n";
	my $ulFsOffset=$kaa-$image_base;
	$kaa=$ptag_struct->{'rootfsLen'} or die "Illegal image ! Tag crc failed.(rootfsLen)\n";
	my $ulFsLen=$kaa+0;

	my $ulTagOffset = $ulFsOffset - $file_tag_len;
	my $ulTagLen = $file_tag_len;


	   printf("\tImage components offsets\n");
	    printf("\timage base              : 0x%8.8x\n",
		$image_base);
	    printf("\tCFE offset              : 0x%8.8x    -- Length: 0x%x\n",
		$ulCfeOffset, $ulCfeLen);
	    printf("\tNVRAM offset            : 0x%8.8x    -- Length: 0x%x\n",
		$ulNvramOffset + $ulCfeOffset, $ulNvramLen);
	    printf("\tfile tag offset         : 0x%8.8x    -- Length: 0x%x\n",
		$ulTagOffset, $ulTagLen);
	    printf("\trootfs offset           : 0x%8.8x    -- Length: 0x%x\n",
		$ulFsOffset, $ulFsLen);
	    printf("\tkernel offset           : 0x%8.8x    -- Length: 0x%x\n",
		$ulKernelOffset, $ulKernelLen);


	my $outbuf="\377" x ($ulKernelOffset + $ulKernelLen + $psi_size);

	#print ($ulKernelOffset + $ulKernelLen + $psi_size);
	#print "\n---\n";

	open outfile_fd, "> $outputfile" or die "Failed to open $outputfile";
	binmode outfile_fd;

	my $cfebin;
	if ( read (ifile_fd, $cfebin, $ulCfeLen) == $ulCfeLen)
	{
		substr($outbuf, $ulCfeOffset, $ulCfeLen, $cfebin);
	}
	else
	{
		die("File read error $inputfile");
	}

	substr($outbuf, ($ulFsOffset-$file_tag_len), length($ptag), $ptag);


	my $fs;
	if ( read (ifile_fd, $fs, $ulFsLen) == $ulFsLen)
	{
		substr($outbuf, $ulFsOffset, $ulFsLen, $fs);
	}
	else
	{
		die("File read error $inputfile");
	}

	my $kernel;
	if ( read (ifile_fd, $kernel, $ulKernelLen ) == $ulKernelLen)
	{
		substr($outbuf, $ulKernelOffset, $ulKernelLen, $kernel);
	}
	else
	{
		die("File read error $inputfile");
	}
	substr($outbuf, $ulNvramOffset, length($nvram_binary), $nvram_binary);

	print outfile_fd $outbuf;

	my $of_size=length($outbuf);
	printf( "\tThe size of the entire flash image is %d bytes.\n", $of_size);

	close(outfile_fd);
	close(ifile_fd);

}
else
{
	open wholefile_fd, "+< $wholeflashfile" or die "Failed to open wholeflashfile $wholeflashfile\n";
	binmode wholefile_fd;
        my ($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,
           $atime,$mtime,$ctime,$blksize,$blocks)
               = stat(wholefile_fd);
	my $nvram_base=0;
	#read everything except the wfitag
	read(wholefile_fd, $data, $size-$token_len);
	$ctx = new Digest::CRC(width => 32, poly => 0x04c11db7, init => 0xffffffff, xorout => 0, refin => 1, refout => 1);
	$ctx->add($data);
	$csum=$ctx->digest;
	#printf("Original CRC %x\n", $csum);

	my $wfi_tag;
	my $wfi_tag_struct;
	read(wholefile_fd, $wfi_tag, $token_len);
	my $c = Convert::Binary::C->new(%main::config)->parse_file($nvramfile);
	$wfi_tag_struct=$c->unpack('WFI_TAG', $wfi_tag);

	if($csum == $wfi_tag_struct->{'wfiCrc'})
	{
		if($wfi_tag_struct->{'wfiChipId'} == 0x63148 || 
			$wfi_tag_struct->{'wfiChipId'} == 0x63138)
		{
			if(($wfi_tag_struct->{'wfiChipId'} & $pmc_flag_bit) == 1)
			{
				$nvram_base=0x10000;
			}
			else
			{
				my @zero_padding=unpack('I4', $data);
				if($zero_padding[0] == 0  &&
					$zero_padding[1] == 0  &&
					$zero_padding[2] == 0  &&
					$zero_padding[3] == 0)
				{
					$nvram_base=0x10000;
				}
			}
		}
		substr($data, $ulNvramOffset+$nvram_base, length($nvram_binary), $nvram_binary);
		$ctx = new Digest::CRC(width => 32, poly => 0x04c11db7, init => 0xffffffff, xorout => 0, refin => 1, refout => 1);
		$ctx->add($data);
		$csum=$ctx->digest;
		$wfi_tag_struct->{'wfiCrc'}=$csum;
		$wfi_tag=$c->pack('WFI_TAG', $wfi_tag_struct);

		seek(wholefile_fd, 0, 0);
		print wholefile_fd $data;
		print wholefile_fd $wfi_tag;
		close(wholefile_fd);
	}
	else
	{
		printf("CRC mismatch File %X - calculated %X\n", $csum, $wfi_tag_struct->{'wfiCrc'});
	}
	
}

