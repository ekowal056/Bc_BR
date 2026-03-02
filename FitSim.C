////////////
///
/// RooFit Code To Fit The Bc+ data
///
///

using namespace RooFit;


void FitSim(){

	/// Load in Data
	TChain *mctree = new TChain("TupleBcplus2JpsiPiplus/DecayTree");
//	TChain *rtree = new TChain("TupleBcplus2JpsiPiplus/DecayTree");

	mctree->Add("NewTry/FullFilteredSim/*/Bc2Jpsipi_ANA2013-069_allsim.root");
//	rtree->Add("DataPaperCut/*/Bc2Jpsipi_ANA2013-069_alldata.root");

	/// Define Mass Variable and Parameters
	RooRealVar mBc("Bc_MM", "m_{B^+_c}", 6150, 6500);
	mBc.setUnit("MeV");
	mBc.setBins(100);

	
//////////  Define Cut Variables ///////////////
	
	/// Trigger
	RooRealVar Jpsi_L0MuonDecision_TOS("Jpsi_L0MuonDecision_TOS", "Jpsi L0MuonDecision TOS", 0, 1);
	RooRealVar Jpsi_L0DiMuonDecision_TOS("Jpsi_L0DiMuonDecision_TOS", "Jpsi L0DiMuonDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt1TrackMVADecision_TOS("Jpsi_Hlt1TrackMVADecision_TOS", "Jpsi Hlt1TrackMVADecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt1TrackMuonDecision_TOS("Jpsi_Hlt1TrackMuonDecision_TOS", "Jpsi Hlt1TrackMuonDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt1DiMuonHighMassDecision_TOS("Jpsi_Hlt1DiMuonHighMassDecision_TOS", "Jpsi Hlt1DiMuonHighMassDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", "Jpsi Hlt2DiMuonDetachedJPsiDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS("Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS", "Jpsi Hlt2DiMuonDetachedHeavyDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt2TopoMu2BodyDecision_TOS("Jpsi_Hlt2TopoMu2BodyDecision_TOS", "Jpsi Hlt2TopoMu2BodyDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt2TopoMu3BodyDecision_TOS("Jpsi_Hlt2TopoMu3BodyDecision_TOS", "Jpsi Hlt2TopoMu3BodyDecision TOS", 0, 1);

	/// MC Truth Cut Variables
	RooRealVar Bc_TRUEID("Bc_TRUEID", "Bc TRUEID", -600, 600);
	RooRealVar Jpsi_TRUEID("Jpsi_TRUEID", "Jpsi TRUEID", -450, 450);
	RooRealVar Bc_BKGCAT("Bc_BKGCAT", "Bc BKGCAT", 0, 130);
	RooRealVar Jpsi_BKGCAT("Jpsi_BKGCAT", "Jpsi BKGCAT", 0, 130);
	RooRealVar BachPi_isMuon("BachPi_isMuon", "BachPi isMuon", 0, 1);

	////// Main Cuts
	// J/psi
	RooRealVar Jpsi_M("Jpsi_M", "M(mu^+ mu^-))", 2996.916, 3196.916);
	RooRealVar Jpsi_ENDVERTEX_CHI2("Jpsi_ENDVERTEX_CHI2", "Jpsi ENDVERTEX CHI2",0,20);
	RooRealVar Jpsi_ENDVERTEX_NDOF("Jpsi_ENDVERTEX_NDOF", "Jpsi ENDVERTEX NDOF", 0 , 3);
	RooRealVar Jpsi_FDCHI2_OWNPV("Jpsi_FDCHI2_OWNPV", "Jpsi FDCHI2 OWNPV", 0,7000000);
	RooRealVar Jpsi_PT("Jpsi_PT", "Jpsi PT", 0, 40000);

	RooRealVar Jpsi_PX("Jpsi_PX","Jpsi PX",-15000,25000);
	RooRealVar Jpsi_PY("Jpsi_PY","Jpsi PY",-15000,25000);
	
	// J/psi muons
	RooRealVar MuM_PIDmu("MuM_PIDmu", "MuM PIDmu", 0, 16);
	RooRealVar MuP_PIDmu("MuP_PIDmu", "MuP PIDmu", 0, 16);
	RooRealVar MuM_PT("MuM_PT", "MuM PT", 0, 35000);
	RooRealVar MuP_PT("MuP_PT","MuP PT", 0, 35000);
	RooRealVar MuM_TRACK_CHI2NDOF("MuM_TRACK_CHI2NDOF", "MuM TRACK CHI2NDOF", 0, 5);
	RooRealVar MuP_TRACK_CHI2NDOF("MuP_TRACK_CHI2NDOF", "MuP TRACK CHI2NDOF", 0, 5);
	RooRealVar MuM_IPCHI2_OWNPV("MuM_IPCHI2_OWNPV", "MuM IPCHI2 OWNPV", 0, 3000000);
	RooRealVar MuP_IPCHI2_OWNPV("MuP_IPCHI2_OWNPV", "MuP IPCHI2 OWNPV", 0 ,3000000);

	RooRealVar MuM_PX("MuM_PX","MuM PX",-10000,10000);
	RooRealVar MuM_PY("MuM_PY","MuM PY",-10000,15000);
       	RooRealVar MuM_PZ("MuM_PZ","MuM PZ",0,300000);
	RooRealVar MuM_P("MuM_P","MuM P",0,300000);
	RooRealVar MuP_PX("MuP_PX","MuP PX",-10000,9000);
       	RooRealVar MuP_PY("MuP_PY","MuP PY",-10000,15000); 
	RooRealVar MuP_PZ("MuP_PZ","MuP PZ",0,300000); 
	RooRealVar MuP_P("MuP_P","MuP P",0,300000);
	
	// Bc
	RooRealVar Bc_ENDVERTEX_CHI2("Bc_ENDVERTEX_CHI2", "Bc_ENDVERTEX_CHI2", 0, 4000000);
	RooRealVar Bc_ENDVERTEX_NDOF("Bc_ENDVERTEX_NDOF", "Bc ENDVERTEX NDOF", 0, 4);


	 RooRealVar Bc_FD_OWNPV("Bc_FD_OWNPV","Bc FD OWNPV",0,48);
	 RooRealVar Bc_M ("Bc_M","Bc M",4000,24000);
	 RooRealVar Bc_P("Bc_P","Bc P",0,900000);

	// Bach Particle
	RooRealVar BachPi_PT("BachPi_PT", "BachPi PT", 0, 80000);
	RooRealVar BachPi_TRACK_CHI2NDOF("BachPi_TRACK_CHI2NDOF", "BachPi TRACK CHI2NDOF", 0, 5);
	RooRealVar BachPi_IPCHI2_OWNPV("BachPi_IPCHI2_OWNPV", "BachPi IPCHI2 OWNPV", 0, 1400000);
	RooRealVar BachPi_PIDK("BachPi_PIDK", "BachPi PIDK", -300, 200);

	RooRealVar BachPi_PX("BachPi_PX","BachPi PX",-10000,35000);
	RooRealVar BachPi_PY("BachPi_PY","BachPi PY",-65000,20000);
	RooRealVar BachPi_PZ("BachPi_PZ","BachPi PZ",0,800000);
	RooRealVar BachPi_P("BachPi_P","BachPi P",0,800000);

////////// Create RooDataSets //////////////////
	
	RooDataSet *mc = new RooDataSet("mc", "2018 Monte Carlo Sim", mctree, RooArgList(mBc,Bc_TRUEID, Jpsi_TRUEID, Jpsi_BKGCAT, Bc_BKGCAT, BachPi_isMuon),//Jpsi_L0MuonDecision_TOS,Jpsi_L0DiMuonDecision_TOS,Jpsi_Hlt1TrackMVADecision_TOS,Jpsi_Hlt1TrackMuonDecision_TOS,Jpsi_Hlt1DiMuonHighMassDecision_TOS,Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS,Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS,Jpsi_Hlt2TopoMu2BodyDecision_TOS,Jpsi_Hlt2TopoMu3BodyDecision_TOS, Bc_TRUEID, Jpsi_TRUEID, Jpsi_BKGCAT, Bc_BKGCAT, BachPi_isMuon),
//			"(Jpsi_L0MuonDecision_TOS==1 || Jpsi_L0DiMuonDecision_TOS==1)" 
//			"&& (( Jpsi_Hlt1TrackMVADecision_TOS==1|| Jpsi_Hlt1TrackMuonDecision_TOS==1) || Jpsi_Hlt1DiMuonHighMassDecision_TOS==1)" 
//			"&& (( Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1) || (Jpsi_Hlt2TopoMu2BodyDecision_TOS==1|| Jpsi_Hlt2TopoMu3BodyDecision_TOS==1))"
			" (TMath::Abs(Bc_TRUEID) == 541 && TMath::Abs(Jpsi_TRUEID) == 443)"
			"&& ((Jpsi_BKGCAT == 0 && Bc_BKGCAT == 0) || (Jpsi_BKGCAT == 50 && Bc_BKGCAT == 50))"
			"&& (BachPi_isMuon == 0)"
		);

	//RooDataSet *data = new RooDataSet("data", "2018 Run2 Data", rtree, RooArgList(mBc,Jpsi_L0MuonDecision_TOS,Jpsi_L0DiMuonDecision_TOS, Jpsi_Hlt1TrackMVADecision_TOS,Jpsi_Hlt1TrackMuonDecision_TOS,Jpsi_Hlt1DiMuonHighMassDecision_TOS,Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS,Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS,Jpsi_Hlt2TopoMu2BodyDecision_TOS,Jpsi_Hlt2TopoMu3BodyDecision_TOS, MuM_PIDmu, MuP_PIDmu, MuM_PT, MuP_PT, MuM_TRACK_CHI2NDOF, MuP_TRACK_CHI2NDOF, Jpsi_M, Jpsi_ENDVERTEX_CHI2, Jpsi_ENDVERTEX_NDOF, Jpsi_FDCHI2_OWNPV, Jpsi_PT, MuM_IPCHI2_OWNPV, MuP_IPCHI2_OWNPV, BachPi_PT, BachPi_TRACK_CHI2NDOF, BachPi_IPCHI2_OWNPV, BachPi_PIDK, Bc_ENDVERTEX_CHI2, Bc_ENDVERTEX_NDOF, BachPi_PX, BachPi_PY, BachPi_PZ, BachPi_P, MuP_PX, MuP_PY, MuP_PZ, MuP_P, MuM_PX, MuM_PY, MuM_PZ, MuM_P, Jpsi_PX, Jpsi_PY, Bc_FD_OWNPV, Bc_M, Bc_P), 
	//"(Jpsi_L0MuonDecision_TOS==1 || Jpsi_L0DiMuonDecision_TOS==1)"
         //       	"&& (( Jpsi_Hlt1TrackMVADecision_TOS==1|| Jpsi_Hlt1TrackMuonDecision_TOS==1) || Jpsi_Hlt1DiMuonHighMassDecision_TOS==1)"
          //      	"&& (( Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1) || (Jpsi_Hlt2TopoMu2BodyDecision_TOS==1|| Jpsi_Hlt2TopoMu3BodyDecision_TOS==1))"
	//	 	"&&( MuM_PIDmu >0 && MuM_PIDmu > 0)"
	//		"&& ( MuM_PT>900 && MuP_PT > 900)"
	//		"&& (MuM_TRACK_CHI2NDOF<4.0 && MuP_TRACK_CHI2NDOF<4.0 )"
	//		"&& (Jpsi_M > 3040 && Jpsi_M < 3140)"
	//		"&& (Jpsi_ENDVERTEX_CHI2/Jpsi_ENDVERTEX_NDOF <9.0)"
	//		"&& Jpsi_FDCHI2_OWNPV>5.0"
	//		"&& Jpsi_PT>1500"
	//		"&& MuM_IPCHI2_OWNPV>9.0, MuP_IPCHI2_OWNPV>9.0"
	//		"&& BachPi_PT>1000"
	//		"&& BachPi_TRACK_CHI2NDOF < 4.0"
	//		"&& BachPi_IPCHI2_OWNPV > 9.0"
	//		"&& (((BachPi_PX*MuP_PX) + (BachPi_PY*MuP_PY) + (BachPi_PZ*MuP_PZ)) /(BachPi_P*MuP_P))<0.9999" //cos(t, mu)
	//		"&& (((BachPi_PX*MuM_PX) + (BachPi_PY*MuM_PY) + (BachPi_PZ*MuM_PZ)) /(BachPi_P*MuM_P))<0.9999"
	//		"&& BachPi_PIDK < 5.0"
	//		"&& (((BachPi_PX*Jpsi_PX) + (BachPi_PY*Jpsi_PY))/ ( std::sqrt(BachPi_PX*BachPi_PX + BachPi_PY*BachPi_PY) * std::sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY)))>-0.8" //cos(t, jpsi)
	//		"&& (Bc_ENDVERTEX_CHI2/Bc_ENDVERTEX_NDOF <9.0)"
	//		"&& (Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/299792458.0)>0.25e-12" //proper lifetime of Bc
	//		);



	///////////// Create Fit Variables and Shape ///////////////////

	RooRealVar mu("mu", "#mu", 6300, 6100, 6400);
	RooRealVar sig("sig", "#sigma", 20, 1, 250);
	RooRealVar sigL("sigL", "#sigmaL", 20, 1, 250);
	RooRealVar alphaL("alphaL", "#alpha_L", 0.5, 0.5,5); // + alpha = tail on left side, - alpha = tail on right side
	RooRealVar nL("nL", "n_L", 2, 1, 100);

	RooRealVar alphaR("alphaR", "#alpha_R", -1.5, -5,0.5); // + alpha = tail on left side, - alpha = tail on right side
	RooRealVar nR("nR", "n_R", 2, 1, 100);
	RooRealVar sigR("sigR", "#sigmaR", 20, 1, 250);
	RooRealVar fracsig("fracsig", "Fraction of Signals", 0.7, 0,1);

		//RooRealVar lambda("lambda", "#lambda", -0.001, -10,0.0);
		//RooRealVar frac("frac", "fraction of Signal vs Background", 0, 1);
		//RooRealVar Nsig("Nsig", "Number of Signal Events", 100, 100, 1e6);
		//RooRealVar Nbg("Nbg", "Number of Background Events", 15000, 1000, 1e6);
	RooGaussian sig_g("sig_g", "Signal Gaussian", mBc, mu, sig);

	// Double Crystal Ball

	RooCBShape signalL("signalL", "Signal Crystal Ball Left", mBc, mu, sigL, alphaL, nL);
	RooCBShape signalR("signalR", "Signal Crystal Ball Right", mBc, mu, sigR, alphaR, nR);
	RooAddPdf doublecb("doublecb", "double cb signal", RooArgList(signalL, signalR), RooArgList(fracsig));

	sig_g.fitTo(*mc);
	doublecb.fitTo(*mc);

	RooPlot *mframe = mBc.frame();
	mc->plotOn(mframe); // PLot the Data on plot
        sig_g.plotOn(mframe);
        RooHist *pulls=mframe->pullHist(); //Grabs from the last two things plotted

	RooPlot *mframe2 = mBc.frame();
        mc->plotOn(mframe2); // PLot the Data on plot
        doublecb.plotOn(mframe2);
        RooHist *pulls2=mframe2->pullHist(); 

        // Style and Decoration Fun!
        //model.plotOn(mframe, Components("*expo*"), LineStyle(kDashed), LineColor(kRed));
        //model.plotOn(mframe, Components("*sig*"), FillColor(kViolet), FillStyle(3001), DrawOption("F"));
        sig_g.paramOn(mframe);
	doublecb.paramOn(mframe2);

	TCanvas *c1 = new TCanvas("c1", "c1", 480, 600);
        c1->Divide(2,2);
        c1->cd(1);
        mframe->Draw(); //Draw the plot

        c1->cd(3);

        pulls->Draw();

	c1->cd(2);
	mframe2->Draw(); //Draw the plot

        c1->cd(4);

        pulls2->Draw();


        ///////////// 

        // Define a Range
        //mBc.setRange("sigrange", 5220, 5340); // Just an internal property of mB so does not need a nice name
        //RooAbsReal *intBG = expoBG.createIntegral(RooArgSet(mBc), NormSet(mBc), Range("sigrange"));

	//cout << "\n ##################### \n BG integral is " << Nbg.getVal()*intBG->getVal() << "+/-" << Nbg.getError()*intBG->getVal() << endl;









}



