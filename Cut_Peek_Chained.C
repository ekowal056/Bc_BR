{


TChain *mctree = new TChain("TupleBcplus2JpsiPiplus/DecayTree");
TChain *rtree = new TChain("TupleBcplus2JpsiPiplus/DecayTree");

mctree->Add("NewTry/FullFilteredSim/*/Bc2Jpsipi_ANA2013-069_allsim.root");
rtree->Add("FullFilters_Data/*/Bc2Jpsipi_ANA2013-069_alldata.root");

TString cut_name = "Bc_IPCHI2_OWNPV";
double cut_low = 0;
double cut_high = 20;

//double MC_Bc_M, MC_Bc_P, MC_Bc_FD_OWNPV;

//mctree->SetBranchAddress("Bc_M", &MC_Bc_M);
//mctree->SetBranchAddress("Bc_P", &MC_Bc_P);
//mctree->SetBranchAddress("Bc_FD_OWNPV", &MC_Bc_FD_OWNPV);

//constexpr double c = 299792458.0; 

double MC_Mu_P, MC_Mu_PX, MC_Mu_PY, MC_Mu_PZ;
double MC_BachPi_P, MC_BachPi_PX, MC_BachPi_PY, MC_BachPi_PZ;

//mctree->SetBranchAddress("MuP_P", &MC_Mu_P);
//mctree->SetBranchAddress("MuP_PX", &MC_Mu_PX);
//mctree->SetBranchAddress("MuP_PY", &MC_Mu_PY);
//mctree->SetBranchAddress("MuP_PZ", &MC_Mu_PZ);
//mctree->SetBranchAddress("BachPi_P", &MC_BachPi_P);
mctree->SetBranchAddress("BachPi_PX", &MC_BachPi_PX);
mctree->SetBranchAddress("BachPi_PY", &MC_BachPi_PY);
//mctree->SetBranchAddress("BachPi_PZ", &MC_BachPi_PZ);

double MC_Jpsi_PX, MC_Jpsi_PY;
mctree->SetBranchAddress("Jpsi_PX", &MC_Jpsi_PX);
mctree->SetBranchAddress("Jpsi_PY", &MC_Jpsi_PY);



// Grab MC Filtering Variables
double MC_Bc_mass;//, MC_CUT;
int MC_Bc_TRUEID, MC_Jpsi_TRUEID, MC_Bc_BKGCAT, MC_Jpsi_BKGCAT;
bool MC_BachPi_isMuon;

mctree->SetBranchAddress("Bc_MM", &MC_Bc_mass);
mctree->SetBranchAddress("Bc_TRUEID", &MC_Bc_TRUEID);
mctree->SetBranchAddress("Jpsi_TRUEID", &MC_Jpsi_TRUEID);
mctree->SetBranchAddress("Bc_BKGCAT", &MC_Bc_BKGCAT);
mctree->SetBranchAddress("Jpsi_BKGCAT", &MC_Jpsi_BKGCAT);
mctree->SetBranchAddress("BachPi_isMuon", &MC_BachPi_isMuon);
//mctree->SetBranchAddress(cut_name, &MC_CUT);

// Trigger Variables
bool MC_Jpsi_L0MuonDecision_TOS, MC_Jpsi_L0DiMuonDecision_TOS;
bool MC_Jpsi_Hlt1TrackMVADecision_TOS, MC_Jpsi_Hlt1TrackMuonDecision_TOS;
bool MC_Jpsi_Hlt1DiMuonHighMassDecision_TOS;
bool MC_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS, MC_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS;
bool MC_Jpsi_Hlt2TopoMu2BodyDecision_TOS, MC_Jpsi_Hlt2TopoMu3BodyDecision_TOS;

mctree->SetBranchAddress("Jpsi_L0MuonDecision_TOS", &MC_Jpsi_L0MuonDecision_TOS);
mctree->SetBranchAddress("Jpsi_L0DiMuonDecision_TOS", &MC_Jpsi_L0DiMuonDecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt1TrackMVADecision_TOS", &MC_Jpsi_Hlt1TrackMVADecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt1TrackMuonDecision_TOS", &MC_Jpsi_Hlt1TrackMuonDecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_TOS", &MC_Jpsi_Hlt1DiMuonHighMassDecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", &MC_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS", &MC_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt2TopoMu2BodyDecision_TOS", &MC_Jpsi_Hlt2TopoMu2BodyDecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt2TopoMu3BodyDecision_TOS", &MC_Jpsi_Hlt2TopoMu3BodyDecision_TOS);




// Define MC Mass and Variable Histograms
TH1D *mc_mass_hist = new TH1D("mc_mass_hist", "MC B_c^+ Mass Distribution", 100, 6200, 6350);
TH1D *mc_cut_hist = new TH1D("mc_cut_hist", "MC B_c^+ Distribution of " + cut_name, 100, cut_low, cut_high);

int n = mctree->GetEntries();

for (int i=0; i<n; i++){
	mctree->GetEntry(i);
	// Trigger Cut
	if ( (MC_Jpsi_L0MuonDecision_TOS==1 || MC_Jpsi_L0DiMuonDecision_TOS==1) && (( MC_Jpsi_Hlt1TrackMVADecision_TOS==1|| MC_Jpsi_Hlt1TrackMuonDecision_TOS==1) || MC_Jpsi_Hlt1DiMuonHighMassDecision_TOS==1) && (( MC_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || MC_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1) || (MC_Jpsi_Hlt2TopoMu2BodyDecision_TOS==1|| MC_Jpsi_Hlt2TopoMu3BodyDecision_TOS==1))){
		// Truth Cuts
		if ( (TMath::Abs(MC_Bc_TRUEID) == 541 && TMath::Abs(MC_Jpsi_TRUEID) == 443) && ((MC_Jpsi_BKGCAT == 0 && MC_Bc_BKGCAT == 0) || (MC_Jpsi_BKGCAT == 50 && MC_Bc_BKGCAT == 50))  && (MC_BachPi_isMuon == 0)){
			mc_mass_hist->Fill(MC_Bc_mass);
			mc_cut_hist->Fill(MC_CUT);
			//mc_cut_hist->Fill(MC_Bc_FD_OWNPV*10e-3*MC_Bc_M/MC_Bc_P/c);
			//mc_cut_hist->Fill( ((MC_BachPi_PX*MC_Mu_PX) + (MC_BachPi_PY*MC_Mu_PY) + (MC_BachPi_PZ*MC_Mu_PZ)) /(MC_BachPi_P*MC_Mu_P) );
                        //mc_cut_hist->Fill(( (MC_BachPi_PX*MC_Jpsi_PX) + (MC_BachPi_PY*MC_Jpsi_PY))/ ( std::sqrt(MC_BachPi_PX*MC_BachPi_PX + MC_BachPi_PY*MC_BachPi_PY) * std::sqrt(MC_Jpsi_PX*MC_Jpsi_PX + MC_Jpsi_PY*MC_Jpsi_PY)));

		}}

}


// Grab Upper and Lower Mass Backgrounds

//double Bc_M, Bc_P, Bc_FD_OWNPV;
//rtree->SetBranchAddress("Bc_M", &Bc_M);
//rtree->SetBranchAddress("Bc_P", &Bc_P);
//rtree->SetBranchAddress("Bc_FD_OWNPV", &Bc_FD_OWNPV);

double Mu_P, Mu_PX, Mu_PY, Mu_PZ;
double BachPi_P, BachPi_PX, BachPi_PY, BachPi_PZ;

rtree->SetBranchAddress("MuP_P", &Mu_P);
rtree->SetBranchAddress("MuP_PX", &Mu_PX);
rtree->SetBranchAddress("MuP_PY", &Mu_PY);
rtree->SetBranchAddress("MuP_PZ", &Mu_PZ);
rtree->SetBranchAddress("BachPi_P", &BachPi_P);
rtree->SetBranchAddress("BachPi_PX", &BachPi_PX);
rtree->SetBranchAddress("BachPi_PY", &BachPi_PY);
rtree->SetBranchAddress("BachPi_PZ", &BachPi_PZ);

double Jpsi_PX, Jpsi_PY;
rtree->SetBranchAddress("Jpsi_PX", &Jpsi_PX);
rtree->SetBranchAddress("Jpsi_PY", &Jpsi_PY);


double Bc_mass;//, CUT;

rtree->SetBranchAddress("Bc_MM", &Bc_mass);
//rtree->SetBranchAddress(cut_name, &CUT);

TH1D *mass_low_hist = new TH1D("mass_low_hist", "Lower than Signal B_c^+ Mass Distribution", 100, 3000, 6200);
TH1D *mass_high_hist = new TH1D("mass_high_hist", "Higher than Signal B_c^+ Mass Distribution", 100, 6350, 9000);

TH1D *cut_low_hist = new TH1D("cut_low_hist", "Lower than Signal B_c^+ Distribution of " + cut_name, 100, cut_low, cut_high);
TH1D *cut_high_hist = new TH1D("cut_high_hist", "Higher than Signal B_c^+ Distribution of " + cut_name, 100, cut_low, cut_high);


bool R_Jpsi_L0MuonDecision_TOS, R_Jpsi_L0DiMuonDecision_TOS;
bool R_Jpsi_Hlt1TrackMVADecision_TOS, R_Jpsi_Hlt1TrackMuonDecision_TOS;
bool R_Jpsi_Hlt1DiMuonHighMassDecision_TOS;
bool R_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS, R_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS;
bool R_Jpsi_Hlt2TopoMu2BodyDecision_TOS, R_Jpsi_Hlt2TopoMu3BodyDecision_TOS;

rtree->SetBranchAddress("Jpsi_L0MuonDecision_TOS", &R_Jpsi_L0MuonDecision_TOS);
rtree->SetBranchAddress("Jpsi_L0DiMuonDecision_TOS", &R_Jpsi_L0DiMuonDecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt1TrackMVADecision_TOS", &R_Jpsi_Hlt1TrackMVADecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt1TrackMuonDecision_TOS", &R_Jpsi_Hlt1TrackMuonDecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_TOS", &R_Jpsi_Hlt1DiMuonHighMassDecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", &R_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS", &R_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt2TopoMu2BodyDecision_TOS", &R_Jpsi_Hlt2TopoMu2BodyDecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt2TopoMu3BodyDecision_TOS", &R_Jpsi_Hlt2TopoMu3BodyDecision_TOS);

std::cout<< "Finished MC FIlter" << std::endl;

int m = rtree->GetEntries();

for (int i=0; i<m; i++){
        rtree->GetEntry(i);

	if ((R_Jpsi_L0MuonDecision_TOS==1 || R_Jpsi_L0DiMuonDecision_TOS==1) && (( R_Jpsi_Hlt1TrackMVADecision_TOS==1|| R_Jpsi_Hlt1TrackMuonDecision_TOS==1) || R_Jpsi_Hlt1DiMuonHighMassDecision_TOS==1) && (( R_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || R_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1)  || (R_Jpsi_Hlt2TopoMu2BodyDecision_TOS==1|| R_Jpsi_Hlt2TopoMu3BodyDecision_TOS==1))){
	
		if (Bc_mass < 6200){
			mass_low_hist->Fill(Bc_mass);
			cut_low_hist->Fill(CUT);
			//cut_low_hist->Fill(Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/c);
			//cut_low_hist->Fill( ((BachPi_PX*Mu_PX) + (BachPi_PY*Mu_PY) + (BachPi_PZ*Mu_PZ)) /(BachPi_P*Mu_P) );
                        //cut_low_hist->Fill(( (BachPi_PX*Jpsi_PX) + (BachPi_PY*Jpsi_PY))/ ( std::sqrt(BachPi_PX*BachPi_PX + BachPi_PY*BachPi_PY) * std::sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY)));


		}
		if (Bc_mass > 6350){
			mass_high_hist->Fill(Bc_mass);
                	cut_high_hist->Fill(CUT);
			//cut_high_hist->Fill(Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/c);
			//cut_high_hist->Fill( ((BachPi_PX*Mu_PX) + (BachPi_PY*Mu_PY) + (BachPi_PZ*Mu_PZ)) /(BachPi_P*Mu_P) );
			//cut_high_hist->Fill(( (BachPi_PX*Jpsi_PX) + (BachPi_PY*Jpsi_PY))/ ( std::sqrt(BachPi_PX*BachPi_PX + BachPi_PY*BachPi_PY) * std::sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY)));

	}}

}

mc_cut_hist->SetFillStyle(3001);
mc_cut_hist->SetFillColor(kRed);

cut_low_hist->SetFillStyle(3325);
cut_low_hist->SetFillColor(kAzure-3);

cut_high_hist->SetFillStyle(3352);
cut_high_hist->SetFillColor(kOrange-3);



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
cut_low_hist->Draw();

look->cd(5);
mc_cut_hist->Draw();

look->cd(6);
cut_high_hist->Draw();



TCanvas *compare = new TCanvas("compare", "Overlapping Histograms of MC Signal and Background Data", 1200, 600);

cut_low_hist->Draw();
cut_high_hist->Draw("Same");
mc_cut_hist->Draw("Same");
















}
