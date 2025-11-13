
double Bc_mass, Jpsi_Mass;

TChain *simalltruth = new TChain("TupleBcplus2JpsiPiplus/DecayTree");
simalltruth->Add("AllTruth/*/Bc2Jpsipi_ANA2013-069_SimTruth_all.root");

simalltruth->SetBranchAddress("Bc_M", &Bc_mass);
simalltruth->SetBranchAddress("Jpsi_M", &Jpsi_mass);

