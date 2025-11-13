{


TFile *mcdata = new TFile("Bc2Jpsipi_ANA2013-069_allsim.root", "Read");
TFile *rdata = new TFile("Bc2Jpsipi_ANA2013-069_alldata.root", "Read");

TTree *mctree;
TTree *rtree;


mctree=dynamic_cast<TTree*>(mcdata->Get("TupleBcplus2JpsiPiplus/DecayTree"));
rtree=dynamic_cast<TTree*>(rdata->Get("TupleBcplus2JpsiPiplus/DecayTree"));


// Grab MC Filtering Variables
double MC_Bc_mass, MC_Bc_PT;
int MC_Bc_TRUEID, MC_Jpsi_TRUEID, MC_Bc_BKGCAT, MC_Jpsi_BKGCAT;
bool MC_BachPi_isMuon;

mctree->SetBranchAddress("Bc_MM", &MC_Bc_mass);
mctree->SetBranchAddress("Bc_TRUEID", &MC_Bc_TRUEID);
mctree->SetBranchAddress("Jpsi_TRUEID", &MC_Jpsi_TRUEID);
mctree->SetBranchAddress("Bc_BKGCAT", &MC_Bc_BKGCAT);
mctree->SetBranchAddress("Jpsi_BKGCAT", &MC_Jpsi_BKGCAT);
mctree->SetBranchAddress("BachPi_isMuon", &MC_BachPi_isMuon);
mctree->SetBranchAddress("Bc_PT", &MC_Bc_PT);

// Define MC Mass and Variable Histograms
TH1D *mc_mass_hist = new TH1D("mc_mass_hist", "MC B_c^+ Mass Distribution", 100, 6200, 6350);
TH1D *mc_pt_hist = new TH1D("mc_pt_hist", "MC B_c^+ PT Distribution", 100, 0, 35000);

int n = mctree->GetEntries();

for (int i=0; i<n; i++){
	mctree->GetEntry(i);

	if ( (TMath::Abs(MC_Bc_TRUEID) == 541 && TMath::Abs(MC_Jpsi_TRUEID) == 443) && ((MC_Jpsi_BKGCAT == 0 && MC_Bc_BKGCAT == 0) || (MC_Jpsi_BKGCAT == 50 && MC_Bc_BKGCAT == 50))  && (MC_BachPi_isMuon == 0)){
		mc_mass_hist->Fill(MC_Bc_mass);
		mc_pt_hist->Fill(MC_Bc_PT);
	
	}

}


// Grab Upper and Lower Mass Backgrounds

double Bc_mass, Bc_PT;

rtree->SetBranchAddress("Bc_MM", &Bc_mass);
rtree->SetBranchAddress("Bc_PT", &Bc_PT);

TH1D *mass_low_hist = new TH1D("mass_low_hist", "Lower than Signal B_c^+ Mass Distribution", 100, 3000, 6200);
TH1D *mass_high_hist = new TH1D("mass_high_hist", "Higher than Signal B_c^+ Mass Distribution", 100, 6350, 9000);

TH1D *pt_low_hist = new TH1D("pt_low_hist", "Lower than Signal B_c^+ PT Distribution", 100, 0, 35000);
TH1D *pt_high_hist = new TH1D("pt_high_hist", "Higher than Signal B_c^+ PT Distribution", 100, 0, 35000);

int m = rtree->GetEntries();

for (int i=0; i<m; i++){
        rtree->GetEntry(i);
	
	if (Bc_mass < 6200){
		mass_low_hist->Fill(Bc_mass);
		pt_low_hist->Fill(Bc_PT);
	}
	if (Bc_mass > 6350){
		mass_high_hist->Fill(Bc_mass);
                pt_high_hist->Fill(Bc_PT);
	}

}




TCanvas *look = new TCanvas("look", "Histograms of MC and Real Data", 1200,600);

look-> Divide(3,2);

look->cd(1);
mass_low_hist->Draw();

look->cd(2);
mc_mass_hist->Draw();

//->SetTitle("MC Mass of the Bc");

// Draw("Stuff>>histame", "cuts")
// Draw("stuff>>histname(nbins, min, max)")
// Rdataframe: faster way to do draw stuff (Emily) (Root Script tutorial)

// Fix TISTOS

look->cd(3);
mass_high_hist->Draw();

look->cd(4);
pt_low_hist->Draw();

look->cd(5);
mc_pt_hist->Draw();

look->cd(6);
pt_high_hist->Draw();



















}
