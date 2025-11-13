////////////
///
///
///
///


using namespace RooFit;

void BcJpsi_mass()
{

double Bc_mass, Jpsi_mass;
int Bc_ID, bc_bkgcat, jpsi_bkgcat;

TChain *simalltruth = new TChain("TupleBcplus2JpsiPiplus/DecayTree");
simalltruth->Add("AllTruth/*/Bc2Jpsipi_ANA2013-069_SimTruth_all.root");

simalltruth->SetBranchAddress("Bc_M", &Bc_mass);
simalltruth->SetBranchAddress("Jpsi_M", &Jpsi_mass);

simalltruth->SetBranchAddress("Bc_TRUEID", &Bc_ID);
simalltruth->SetBranchAddress("Bc_BKGCAT", &bc_bkgcat);
simalltruth->SetBranchAddress("Jpsi_BKGCAT", &jpsi_bkgcat);


TH2D *mass_hist0 = new TH2D("mass_hist0", "2D Histogram of B_{c} and J/ psi Masses", 100, 6000,6500, 100, 2750, 3250);
TH2D *mass_hist50 = new TH2D("mass_hist50", "2D Histogram of B_{c} and J/ psi Masses", 100, 6000,6500, 100, 2750, 3250);

int n = simalltruth->GetEntries();


for (int i = 0; i<n; i++){
	simalltruth->GetEntry(i);

	if(Bc_ID==541){
	    if(bc_bkgcat==0 && jpsi_bkgcat==0){
                mass_hist0->Fill(Bc_mass, Jpsi_mass);
                };
            if(bc_bkgcat==50 && jpsi_bkgcat==50){
                mass_hist50->Fill(Bc_mass, Jpsi_mass);
                }};
}

TCanvas *bcjpsi_2d = new TCanvas("bcjpsi_2d", "Bc+ and J/psi Mass 2D Histogram", 1200,600);

bcjpsi_2d->Divide(2,1);

bcjpsi_2d->cd(1);
mass_hist0->Draw();

bcjpsi_2d->cd(2);
mass_hist50->Draw();














}
