//////////////////////
/// 
/// Apply Cuts To JpsiPi
///
////////////////////////////


{
bool sim = false;
bool bkg = true;

///TChain *tree = new TChain("JpsiRecTuple/DecayTree");
TChain *tree = new TChain("DecayTree");

TString filename = "2018_Data_MU_misID_Mcut_prescale.root ";
TString outname = filename;
outname.ReplaceAll("2018_MC_","");
outname.ReplaceAll(".root", "_step1.root");

if (bkg){tree->Add("JpsiMu/BKG18/"+filename);};
if (sim && not bkg){tree->Add("JpsiMu/2018_MC_Bc2JpsiMu.root");};
if (not sim && not bkg){tree->Add("JpsiMu/2018_Data.root");};


if (sim){
	TFile *outfile = nullptr;	
	if (bkg){outfile = new TFile("BKG_Step1/"+outname, "RECREATE");};
	if (not bkg){outfile = new TFile("Bc2JpsiMu_step1_sim18.root", "RECREATE");};
	
	std::cout << "Entries before: " << tree->GetEntries() << std::endl;
	TTree *outtree = tree->CopyTree(
			//"(TMath::Abs(Bc_TRUEID) == 541 && TMath::Abs(Jpsi_TRUEID) == 443) && ((Jpsi_BKGCAT == 0 && Bc_BKGCAT == 0) || (Jpsi_BKGCAT == 50 && Bc_BKGCAT == 50))" //For signal
			"(TMath::Abs(Bc_TRUEID) == 541 && TMath::Abs(Jpsi_TRUEID) == 443) && ((Jpsi_BKGCAT == 0 && (Bc_BKGCAT == 50 || Bc_BKGCAT ==10)) || (Jpsi_BKGCAT == 50 && Bc_BKGCAT == 50))" //For Psi2S, Maybe Chic, JpsiD's, JpsiTau
			//"(Jpsi_BKGCAT==0 || Jpsi_BKGCAT==50) && Bc_BKGCAT > 50 && (TMath::Abs(BachMu_TRUEID)==13 && (TMath::Abs(BachMu_MC_MOTHER_ID) > 400) && MCFromB)" // Only for Buds
			"&& (BachMu_isMuon == 1)" //Only not True for data drive misID
			"&& TMath::Abs(Jpsi_TRUEID) == 443"

			"&& (Jpsi_L0MuonDecision_TOS==1 || Jpsi_L0DiMuonDecision_TOS==1)"
                        //"&& ( Jpsi_Hlt1TrackMVADecision_TOS==1|| Jpsi_Hlt1TrackMuonDecision_TOS==1)   
			"&&(Jpsi_Hlt1DiMuonHighMassDecision_TOS==1)"
			"&& (( Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1))" // || ((Jpsi_Hlt2TopoMu3BodyDecision_TOS==1) || Jpsi_Hlt2TopoMu2BodyDecision_TOS==1)"
                        "&& (MuM_PIDmu >0 && MuM_PIDmu > 0)"
                        "&& ( MuM_PT>900 && MuP_PT > 900)"
                        "&& (MuM_TRACK_CHI2NDOF<3.0 && MuP_TRACK_CHI2NDOF<3.0 )" // Taken down from 4.0 to 3.0
                        "&& (Jpsi_M > 3040 && Jpsi_M < 3140)"
                        "&& (Jpsi_ENDVERTEX_CHI2/Jpsi_ENDVERTEX_NDOF <9.0)"
                        "&& (Jpsi_FDCHI2_OWNPV>5.0)"
                        "&& (Jpsi_PT>1500)"
                        "&& (MuM_IPCHI2_OWNPV>9.0) &&  (MuP_IPCHI2_OWNPV>9.0)"
                        "&& (BachMu_PT>500)"
                        "&& (BachMu_TRACK_CHI2NDOF < 4.0)"
                        "&& (BachMu_IPCHI2_OWNPV > 9.0)"
                        "&& ((((BachMu_PX*MuP_PX) + (BachMu_PY*MuP_PY) + (BachMu_PZ*MuP_PZ)) /(BachMu_P*MuP_P))<0.9999)" //cos(t, mu)
                        "&& ((((BachMu_PX*MuM_PX) + (BachMu_PY*MuM_PY) + (BachMu_PZ*MuM_PZ)) /(BachMu_P*MuM_P))<0.9999)"
                        "&& (BachMu_PIDmu > 0)"
                        "&& ((((BachMu_PX*Jpsi_PX) + (BachMu_PY*Jpsi_PY))/ ( sqrt(BachMu_PX*BachMu_PX + BachMu_PY*BachMu_PY) * sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY)))>-0.8)" //cos(t, jpsi)
                        "&& (Bc_ENDVERTEX_CHI2/Bc_ENDVERTEX_NDOF <9.0)"
                        "&& ((Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/299792458.0)>0.25e-12)" //proper lifetime of Bc
			);
	std::cout << "Entries after: " << outtree->GetEntries() << std::endl;
	outfile->Write();
	outfile->Close();
}
else {
        TFile *outfile = nullptr;
        if (bkg){outfile = new TFile("BKG_Step1/"+outname, "RECREATE");};
        if (not bkg){outfile = new TFile("Bc2JpsiMu_step1_data18.root", "RECREATE");};

	std::cout << "Entries before: " << tree->GetEntries() << std::endl;
	TTree *outtree = tree->CopyTree("(Jpsi_L0MuonDecision_TOS==1 || Jpsi_L0DiMuonDecision_TOS==1)"
                        //"&& (( Jpsi_Hlt1TrackMVADecision_TOS==1|| Jpsi_Hlt1TrackMuonDecision_TOS==1) ||  
                        "&& ((Jpsi_Hlt1DiMuonHighMassDecision_TOS==1))"
                        "&& (( Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1))" // || ((Jpsi_Hlt2TopoMu3BodyDecision_TOS==1) || Jpsi_Hlt2TopoMu2BodyDecision_TOS==1))"
                        "&& (MuM_PIDmu >0 && MuM_PIDmu > 0)"
                        "&& ( MuM_PT>900 && MuP_PT > 900)"
                        "&& (MuM_TRACK_CHI2NDOF<3.0 && MuP_TRACK_CHI2NDOF<3.0 )" // Taken down from 4.0 to 3.0
                        "&& (Jpsi_M > 3040 && Jpsi_M < 3140)"
                        "&& (Jpsi_ENDVERTEX_CHI2/Jpsi_ENDVERTEX_NDOF <9.0)"
                        "&& (Jpsi_FDCHI2_OWNPV>5.0)"
                        "&& (Jpsi_PT>1500)"
                        "&& (MuM_IPCHI2_OWNPV>9.0) &&  (MuP_IPCHI2_OWNPV>9.0)"
                        "&& (BachMu_PT>500)"
                        "&& (BachMu_TRACK_CHI2NDOF < 4.0)"
                        "&& (BachMu_IPCHI2_OWNPV > 9.0)"
                        "&& ((((BachMu_PX*MuP_PX) + (BachMu_PY*MuP_PY) + (BachMu_PZ*MuP_PZ)) /(BachMu_P*MuP_P))<0.9999)" //cos(t, mu)
                        "&& ((((BachMu_PX*MuM_PX) + (BachMu_PY*MuM_PY) + (BachMu_PZ*MuM_PZ)) /(BachMu_P*MuM_P))<0.9999)"
                        "&& (BachMu_PIDmu > 0)"
                        "&& ((((BachMu_PX*Jpsi_PX) + (BachMu_PY*Jpsi_PY))/ ( sqrt(BachMu_PX*BachMu_PX + BachMu_PY*BachMu_PY) * sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY)))>-0.8)" //cos(t, jpsi)
                        "&& (Bc_ENDVERTEX_CHI2/Bc_ENDVERTEX_NDOF <9.0)"
                        "&& ((Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/299792458.0)>0.25e-12)" //proper lifetime of Bc
			//"&& (((Bc_M < 5800) && (Bc_M > 5350)) || ((Bc_M < 6800) && (Bc_M > 8500 )))"
                        );
	std::cout << "Entries after: " << outtree->GetEntries() << std::endl;
	outfile->Write();
	outfile->Close();

}


}
