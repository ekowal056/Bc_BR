void eff_com(){



TFile *JpsiMuRoot = new TFile("Bc2JpsiMu_step1_sim18.root", "Read");
TTree *JpsiMu;
JpsiMu=dynamic_cast<TTree*>(JpsiMuRoot->Get("DecayTree"));
TH1D *full = new TH1D("full", "JpsiMu Visible Bc Mass", 100, 3000, 6500);
TH1D *M = new TH1D("M", "Jpsi Mu Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *MD = new TH1D("MD", "Jpsi Mu Visible Bc Mass >5300MeV, Dira  Cut", 100, 3000, 6500);

JpsiMu->Draw("Bc_M >> full", "", "goff") ;
JpsiMu->Draw("Bc_M >> M", "Bc_M>5300", "goff");
JpsiMu->Draw("Bc_M >> MD", "Bc_M>5300 && Bc_DIRA_OWNPV> 0.9996", "goff");



double fullInt = full->Integral();
double MInt = M->Integral();
double MDInt = MD->Integral();


std::cout<< "Number of starting events: " << fullInt << std::endl;
std::cout<< "Number of events after Bc M: " << MInt << ", " << MInt/fullInt << "% of the full dataset" << std::endl;
std::cout<< "Number of events after Bc_M and DIRA: " << MDInt << ", " << MDInt/fullInt << "% of the full dataset, and " << MDInt/MInt << "% of the Mass cut dataset" << std::endl;




}
