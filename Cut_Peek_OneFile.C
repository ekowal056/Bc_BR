{


TFile *mcdata = new TFile("JpsiMu/2018_MC_Bc2JpsiMu.root", "Read");
TFile *rdata = new TFile("JpsiMu/2018_Data.root", "Read");

TTree *mctree;
TTree *rtree;


mctree=dynamic_cast<TTree*>(mcdata->Get("JpsiRecTuple/DecayTree"));
rtree=dynamic_cast<TTree*>(rdata->Get("JpsiRecTuple/DecayTree"));

TString cut_name = "BachMu_IPCHI2_OWNPV";
double cut_low = 0;
double cut_high = 20;

// Grab MC Filtering Variables
double MC_Bc_mass, MC_CUT;
int MC_Bc_TRUEID, MC_Jpsi_TRUEID, MC_Bc_BKGCAT, MC_Jpsi_BKGCAT;
bool MC_BachPi_isMuon;

mctree->SetBranchAddress("Bc_MM", &MC_Bc_mass);
mctree->SetBranchAddress("Bc_TRUEID", &MC_Bc_TRUEID);
mctree->SetBranchAddress("Jpsi_TRUEID", &MC_Jpsi_TRUEID);
mctree->SetBranchAddress("Bc_BKGCAT", &MC_Bc_BKGCAT);
mctree->SetBranchAddress("Jpsi_BKGCAT", &MC_Jpsi_BKGCAT);
//mctree->SetBranchAddress("BachPi_isMuon", &MC_BachPi_isMuon);
mctree->SetBranchAddress(cut_name, &MC_CUT);

// Trigger Variables
bool MC_Jpsi_L0MuonDecision_TOS, MC_Jpsi_L0DiMuonDecision_TOS;
bool MC_Jpsi_Hlt1TrackMVADecision_TOS, MC_Jpsi_Hlt1TrackMuonDecision_TOS;
bool MC_Jpsi_Hlt1DiMuonHighMassDecision_TOS;
bool MC_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS, MC_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS;
bool MC_Jpsi_Hlt2TopoMu2BodyDecision_TOS, MC_Jpsi_Hlt2TopoMu3BodyDecision_TOS;

mctree->SetBranchAddress("Jpsi_L0MuonDecision_TOS", &MC_Jpsi_L0MuonDecision_TOS);
mctree->SetBranchAddress("Jpsi_L0DiMuonDecision_TOS", &MC_Jpsi_L0DiMuonDecision_TOS);
//mctree->SetBranchAddress("Jpsi_Hlt1TrackMVADecision_TOS", &MC_Jpsi_Hlt1TrackMVADecision_TOS);
//mctree->SetBranchAddress("Jpsi_Hlt1TrackMuonDecision_TOS", &MC_Jpsi_Hlt1TrackMuonDecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_TOS", &MC_Jpsi_Hlt1DiMuonHighMassDecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", &MC_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS);
mctree->SetBranchAddress("Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS", &MC_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS);
//mctree->SetBranchAddress("Jpsi_Hlt2TopoMu2BodyDecision_TOS", &MC_Jpsi_Hlt2TopoMu2BodyDecision_TOS);
//mctree->SetBranchAddress("Jpsi_Hlt2TopoMu3BodyDecision_TOS", &MC_Jpsi_Hlt2TopoMu3BodyDecision_TOS);




// Define MC Mass and Variable Histograms
TH1D *mc_mass_hist = new TH1D("mc_mass_hist", "MC B_c^+ Mass Distribution", 100, 6200, 6350);
TH1D *mc_cut_hist = new TH1D("mc_cut_hist", "MC B_c^+ Distribution of " + cut_name, 100, cut_low, cut_high);

int n = mctree->GetEntries();

for (int i=0; i<n; i++){
	mctree->GetEntry(i);
	// Trigger Cut
	if ((MC_Jpsi_L0MuonDecision_TOS==1 || MC_Jpsi_L0DiMuonDecision_TOS==1) 
			//&& ( MC_Jpsi_Hlt1TrackMVADecision_TOS==1|| MC_Jpsi_Hlt1TrackMuonDecision_TOS==1) 
			&& MC_Jpsi_Hlt1DiMuonHighMassDecision_TOS==1 && ( MC_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || MC_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1)){// && (MC_Jpsi_Hlt2TopoMu2BodyDecision_TOS==1|| MC_Jpsi_Hlt2TopoMu3BodyDecision_TOS==1)){
		// Truth Cuts
		if ( (TMath::Abs(MC_Bc_TRUEID) == 541 && TMath::Abs(MC_Jpsi_TRUEID) == 443) && ((MC_Jpsi_BKGCAT == 0 && MC_Bc_BKGCAT == 0) || (MC_Jpsi_BKGCAT == 50 && MC_Bc_BKGCAT == 50))){//  && (MC_BachMu_isMuon == 1)){
			mc_mass_hist->Fill(MC_Bc_mass);
			mc_cut_hist->Fill(MC_CUT);
	
	}}

}


// Grab Upper and Lower Mass Backgrounds

double Bc_mass, CUT;

rtree->SetBranchAddress("Bc_MM", &Bc_mass);
rtree->SetBranchAddress(cut_name, &CUT);

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
//rtree->SetBranchAddress("Jpsi_Hlt1TrackMVADecision_TOS", &R_Jpsi_Hlt1TrackMVADecision_TOS);
//rtree->SetBranchAddress("Jpsi_Hlt1TrackMuonDecision_TOS", &R_Jpsi_Hlt1TrackMuonDecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_TOS", &R_Jpsi_Hlt1DiMuonHighMassDecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", &R_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS);
rtree->SetBranchAddress("Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS", &R_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS);
//rtree->SetBranchAddress("Jpsi_Hlt2TopoMu2BodyDecision_TOS", &R_Jpsi_Hlt2TopoMu2BodyDecision_TOS);
//rtree->SetBranchAddress("Jpsi_Hlt2TopoMu3BodyDecision_TOS", &R_Jpsi_Hlt2TopoMu3BodyDecision_TOS);



int m = rtree->GetEntries();

for (int i=0; i<m; i++){
        rtree->GetEntry(i);

	if ((R_Jpsi_L0MuonDecision_TOS==1 || R_Jpsi_L0DiMuonDecision_TOS==1) 
			//&& ( R_Jpsi_Hlt1TrackMVADecision_TOS==1|| R_Jpsi_Hlt1TrackMuonDecision_TOS==1) 
			&& R_Jpsi_Hlt1DiMuonHighMassDecision_TOS==1 
			&& ( R_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || R_Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1)){// && (R_Jpsi_Hlt2TopoMu2BodyDecision_TOS==1|| R_Jpsi_Hlt2TopoMu3BodyDecision_TOS==1)){
	
		if (Bc_mass < 6200){
			mass_low_hist->Fill(Bc_mass);
			cut_low_hist->Fill(CUT);
		}
		if (Bc_mass > 6350){
			mass_high_hist->Fill(Bc_mass);
                	cut_high_hist->Fill(CUT);
	}}

}

if (mc_cut_hist->GetMaximum() > 0) {
    mc_cut_hist->Scale(1.0 / mc_cut_hist->GetMaximum());
}

if (cut_high_hist->GetMaximum() > 0) {
    cut_high_hist->Scale(1.0 / cut_high_hist->GetMaximum());
}
if (cut_low_hist->GetMaximum() > 0) {
    cut_low_hist->Scale(1.0 / cut_low_hist->GetMaximum());
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

cut_low_hist->Draw("Hist");
cut_high_hist->Draw("Hist Same");
mc_cut_hist->Draw("Hist Same");
















}
