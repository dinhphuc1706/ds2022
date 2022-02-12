struct file{
	char *fname;
	
	char fcontent;
};

program TRANSFER{
	version TRANSFER_1 {
		int TRANSF(file) = 1;
	}=1;
}=0x23451111;	
