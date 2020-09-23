/*
must have eyecrawl (this was made before eyestep reb came out)
FixIdentitys(Sandbox thread adress);

so far it survived 6 updates
you can redo it to auto update identitys
it isnt hard to do itll prolly take you around 5 min at most
this is from my dumper project i started 6 months ago
*/

int Identity1 =  0;
int Identity2 = 0;


/*
Get All EBP Register values Of A Function
*/
RESULTS GetAllEBPRegOfAFunction(unsigned int Adress) {

	RESULTS	 Offs = RESULTS();
	int edp = EyeCrawl::util::getepilogue(Adress);
	int Addy = 0;
	int r = 0;
	bool s = false;
	while (s == false) {
		Addy = r + Adress;
		if (Addy == edp || Addy > edp) {
			if (EyeCrawl::disassemble(Addy)->r32[1] != R_EBP && EyeCrawl::disassemble(Addy)->offset > 0) {
				Offs.push_back(EyeCrawl::disassemble(Addy)->offset);
			}
			s = true;
		}
		else {
			if (EyeCrawl::disassemble(Addy)->r32[1] != R_EBP && EyeCrawl::disassemble(Addy)->offset > 0) {
				Offs.push_back(EyeCrawl::disassemble(Addy)->offset);
			}
		}

		r = r + 1;
	}
	return Offs;

}
/*
return iden1 and iden2

1st arg must be sandboxthread
*/
RESULTS GetIdentitys(unsigned int sandboxthreadaddy) {
	RESULTS AllEBP = GetAllEBPRegOfAFunction(sandboxthreadaddy);
	RESULTS Identity;
	for (int i = 0; i < AllEBP.size(); i++)
	{
		// identity one is usally more then or equal to 100 but less the 200 (sometimes theres some other stuff to but to filter it make sure it exists twice back by back)
		if (AllEBP[i] < 200 && AllEBP[i] >= 100) {
			if (AllEBP[i] == AllEBP[i + 1]) { // this checks it here
				int ident2 = AllEBP[i];
				int ident1 = AllEBP[i + 2] + AllEBP[i + 3] + AllEBP[i + 4] + AllEBP[i + 5]; // iden1 calc
				Identity.push_back(ident1); // adds first identity	
				Identity.push_back(ident2);
				return Identity;
			}
		}
	}
	Identity.push_back(0);
	Identity.push_back(0);
	return Identity;
}
void FixIdentitys(DWORD SandboxThread) {
	RESULTS ad = GetIdentitys(SandboxThread);
	int Identity1 = ad[0] ;
    int Identity2 =  ad[1];
}
