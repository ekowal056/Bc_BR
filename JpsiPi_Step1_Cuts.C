//////////////////////
/// 
/// Apply Cuts To JpsiPi
///
////////////////////////////


{
TChain *tree = new TChain("TupleBcplus2JpsiPiplus/DecayTree");

//tree->Add("NewTry/FullFilteredSim/*/Bc2Jpsipi_ANA2013-069_allsim.root");
tree->Add("DataPaperCut/*/Bc2Jpsipi_ANA2013-069_alldata.root");

/// Truth Variables?
bool sim = false;

if (sim){
	TFile *outfile = new TFile("Bc2JpsiPi_step1_sim.root", "RECREATE");
	std::cout << "Entries before: " << tree->GetEntries() << std::endl;
	TTree *outtree = tree->CopyTree("(TMath::Abs(Bc_TRUEID) == 541 && TMath::Abs(Jpsi_TRUEID) == 443)"
                        "&& ((Jpsi_BKGCAT == 0 && Bc_BKGCAT == 0) || (Jpsi_BKGCAT == 50 && Bc_BKGCAT == 50))"
                        "&& (BachPi_isMuon == 0)"
			"&& (Jpsi_L0MuonDecision_TOS==1 || Jpsi_L0DiMuonDecision_TOS==1)"
                        //"&& ( Jpsi_Hlt1TrackMVADecision_TOS==1|| Jpsi_Hlt1TrackMuonDecision_TOS==1)   
			" &&((Jpsi_Hlt1DiMuonHighMassDecision_TOS==1) || Jpsi_Hlt1TrackMuonDecision_TOS==1)"
			"&& (( Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1))" // || ((Jpsi_Hlt2TopoMu3BodyDecision_TOS==1) || Jpsi_Hlt2TopoMu2BodyDecision_TOS==1)"
                        "&& (MuM_PIDmu >0 && MuM_PIDmu > 0)"
                        "&& ( MuM_PT>900 && MuP_PT > 900)"
                        "&& (MuM_TRACK_CHI2NDOF<3.0 && MuP_TRACK_CHI2NDOF<3.0 )" // Taken down from 4.0 to 3.0
                        "&& (Jpsi_M > 3040 && Jpsi_M < 3140)"
                        "&& (Jpsi_ENDVERTEX_CHI2/Jpsi_ENDVERTEX_NDOF <9.0)"
                        "&& (Jpsi_FDCHI2_OWNPV>5.0)"
                        "&& (Jpsi_PT>1500)"
                        "&& (MuM_IPCHI2_OWNPV>9.0) &&  (MuP_IPCHI2_OWNPV>9.0)"
                        "&& (BachPi_PT>1000)"
                        "&& (BachPi_TRACK_CHI2NDOF < 4.0)"
                        "&& (BachPi_IPCHI2_OWNPV > 9.0)"
                        "&& ((((BachPi_PX*MuP_PX) + (BachPi_PY*MuP_PY) + (BachPi_PZ*MuP_PZ)) /(BachPi_P*MuP_P))<0.9999)" //cos(t, mu)
                        "&& ((((BachPi_PX*MuM_PX) + (BachPi_PY*MuM_PY) + (BachPi_PZ*MuM_PZ)) /(BachPi_P*MuM_P))<0.9999)"
                        "&& (BachPi_PIDK < 5.0)"
                        "&& ((((BachPi_PX*Jpsi_PX) + (BachPi_PY*Jpsi_PY))/ ( sqrt(BachPi_PX*BachPi_PX + BachPi_PY*BachPi_PY) * sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY)))>-0.8)" //cos(t, jpsi)
                        "&& (Bc_ENDVERTEX_CHI2/Bc_ENDVERTEX_NDOF <9.0)"
                        "&& ((Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/299792458.0)>0.25e-12)" //proper lifetime of Bc
			);
	std::cout << "Entries after: " << outtree->GetEntries() << std::endl;
	//outfile->Write();
	outfile->Close();
}
else {
        TFile *outfile = new TFile("Bc2JpsiPi_step1_data.root", "RECREATE");
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
                        "&& (BachPi_PT>1000)"
                        "&& (BachPi_TRACK_CHI2NDOF < 4.0)"
                        "&& (BachPi_IPCHI2_OWNPV > 9.0)"
                        "&& ((((BachPi_PX*MuP_PX) + (BachPi_PY*MuP_PY) + (BachPi_PZ*MuP_PZ)) /(BachPi_P*MuP_P))<0.9999)" //cos(t, mu)
                        "&& ((((BachPi_PX*MuM_PX) + (BachPi_PY*MuM_PY) + (BachPi_PZ*MuM_PZ)) /(BachPi_P*MuM_P))<0.9999)"
                        "&& (BachPi_PIDK < 5.0)"
                        "&& ((((BachPi_PX*Jpsi_PX) + (BachPi_PY*Jpsi_PY))/ ( sqrt(BachPi_PX*BachPi_PX + BachPi_PY*BachPi_PY) * sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY)))>-0.8)" //cos(t, jpsi)
                        "&& (Bc_ENDVERTEX_CHI2/Bc_ENDVERTEX_NDOF <9.0)"
                        "&& ((Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/299792458.0)>0.25e-12)" //proper lifetime of Bc
			//"&& (((Bc_M < 5800) && (Bc_M > 5350)) || ((Bc_M < 6800) && (Bc_M > 8500 )))"
                        );
	std::cout << "Entries after: " << outtree->GetEntries() << std::endl;
	outfile->Write();
	outfile->Close();

}


}
