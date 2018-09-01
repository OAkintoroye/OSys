Secure S3FS

Modified and additional code added by Olubukola Akintoroye

=================

Pre-Installation
----------------
Please ensure that you have followed the S3FS and OpenSSL installation process. 

If S3FS is not installed please refer to the README file in its folder.

This README file assumes you have completed the S3FS installation process,
created an account on Amazon S3, obtained the S3 identity and credentials, and successfully
mounted your mount point. 

Note: This README file is instruction for Linux machines only.

Thank you!


Installation - Integration of RC4 to S3FS
-----------------------------------------
After downloading the Project Files:

1. Replace the Makefile.am file in /s3fs-fuse/src with the Makefile.am provided
2. Replace the fdcache.cpp file in /s3fs-fuse/src with the fdcache.cpp file provided
3. Include both the rc4test.h and rc4test.cpp files in the /s3fs-fuse/src folder.
4. Use S3FS' method of compiling source files
	cd s3fs-fuse
	./autogen.sh
	./configure
	make
	sudo make install

Note: To locate the encryption function call in fdcache.cpp, simply search 'encryp'.

Demo
----

After installation:

1. Mount the mount point to the local directory. [s3fs mybucket /path/to/mountpoint -o passwd_file= /path/to/passwordfile]
2. Open Amazon S3, log in, and locate bucket.
3. Drag and Drop a file into the mount point

The file should be encrypted in the Amazon S3 bucket.
===================================================================================

Installation - Standalone RC4
-----------------------------
After downloading the Project Files:

1. Add standalonerc42.c and standalonerc42.h to your Desktop folder
2. Enter the following command line:
	gcc standalonerc42.c -I /usr/include/openssl -o standalonerc42 -lssl -lcrypto

Demo
----

After installation:

1. Run the following command line
	./standalonerc42 [inputfilename.extension] [outputfilename.extension]

Note: When typing the command line, exclude the brackets. Also note that this standalone is not 
compatible with the OpenSSL installed in Ubuntu.


