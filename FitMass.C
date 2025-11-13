////////////
///
///
///
///


using namespace RooFit;

void FitMass()
{

double mass;

TChain *simalltruth = new TChain("TupleBcplus2JpsiPiplus/DecayTree");
simalltruth->Add("AllTruth/*/Bc2Jpsipi_ANA2013-069_SimTruth_all.root");

simalltruth->SetBranchAddress("Bc_M", &mass);

RooRealVar mBc("Bc_M", "m_{B_{C}}", 6000, 6500);
RooRealVar BctrueID("Bc_TRUEID", "B_{c} TrueID", -600, 600);
RooRealVar JpsitrueID("Jpsi_TRUEID", "J/psi True ID", -600, 600);
RooRealVar BcBKGCAT("Bc_BKGCAT", "B_{c} Background Catagory", 0, 60);
RooRealVar JpsiBKGCAT("Jpsi_BKGCAT", "J/psi Background Catagory", 0, 60);
RooRealVar PiIsMuon("piplus_isMuon", "Pi^{+} isMuon", 0, 1);
mBc.setUnit("MeV");
mBc.setBins(100);

RooDataSet *data = new RooDataSet("data", "data", simalltruth, RooArgList(mBc,BctrueID, JpsitrueID, BcBKGCAT, JpsiBKGCAT, PiIsMuon), "(TMath::Abs(Bc_TRUEID) == 541 && TMath::Abs(Jpsi_TRUEID) == 443) && (Jpsi_BKGCAT == 0 && Bc_BKGCAT == 0)  && (piplus_isMuon == 0)");
RooDataSet *data50 = new RooDataSet("data", "data", simalltruth, RooArgList(mBc,BctrueID, JpsitrueID, BcBKGCAT, JpsiBKGCAT, PiIsMuon), "(TMath::Abs(Bc_TRUEID) == 541 && TMath::Abs(Jpsi_TRUEID) == 443) && (Jpsi_BKGCAT == 50 && Bc_BKGCAT == 50 ) && (piplus_isMuon == 0)");

RooRealVar mu("mu", "#mu", 6270, 6100, 6400); // Expected mean and room to move
RooRealVar sig1("sig1", "#sigma", 20, 1, 250); // Dont include zero because a divide by zero

RooRealVar sigL("sigL", "#sigmaL", 20, 1, 250);
RooRealVar alphaL("alphaL", "#alpha_L", 0.5, 0.5,5); // + alpha = tail on left side, - alpha = tail on right side
RooRealVar nL("nL", "n_L", 2, 1, 100);

RooRealVar alphaR("alphaR", "#alpha_R", -1.5, -5,0.5); // + alpha = tail on left side, - alpha = tail on right side
RooRealVar nR("nR", "n_R", 2, 1, 100);
RooRealVar sigR("sigR", "#sigmaR", 20, 1, 250);

RooRealVar fracsig("fracsig", "Fraction of Signals", 0.7, 0,1);
RooRealVar gausfrac("gausfrac", "Fraction of additional Gaussians",0.5,  0, 1);

// Fractions
//RooRealVar Nsig("Nsig", "Number of Signal Events", 60000 ,1000, 1e6);
//RooRealVar Nbg("Nbg", "Number of Background Events", 3000 ,1000, 1e6);


// Plain Gaussian Fit
//RooGaussian signalg1("signalg1", "Signal Gaussian", mBc, mu, sig1);

// Double Crystal Ball

RooCBShape signalL("signalL", "Signal Crystal Ball Left", mBc, mu, sigL, alphaL, nL);
RooCBShape signalR("signalR", "Signal Crystal Ball Right", mBc, mu, sigR, alphaR, nR);

RooAddPdf doublecb("doublecb", "double cb signal", RooArgList(signalL, signalR), RooArgList(fracsig));



// Background
//RooExponential expoBG("expoBG", "Exponential Background", mBc, lambda);

//RooAddPdf model("model", "Full Model", RooArgList(doublecb, signalg1), RooArgList(gausfrac));

doublecb.fitTo(*data);

RooPlot *mframe = mBc.frame();
data->plotOn(mframe);
doublecb.plotOn(mframe);
RooHist *pulls=mframe->pullHist();
data50->plotOn(mframe, MarkerColor(kRed), LineColor(kRed));

//signal.plotOn(mframe, Components("*expo*"), LineStyle(kDashed),LineColor(kRed));
doublecb.plotOn(mframe, Components("doublecb"), FillColor(kViolet), FillStyle(3001), DrawOption("F"));
doublecb.paramOn(mframe);

//model.plotOn(mframe, Components("signalg*"),LineStyle(kDashed), LineColor(kRed));

TCanvas *c1 = new TCanvas("c1", "c1", 480, 600);
c1->Divide(1,2);
c1->cd(1);
mframe->Draw(); //Draw the plot

c1->cd(2);
pulls->Draw();




//mBc.setRange("sigrange", 6220, 6330); // Just an internal property of mB so does not need a nice name
//RooAbsReal *intBG = expoBG.createIntegral(RooArgSet(mBc), NormSet(mBc), Range("sigrange"));
//RooAbsReal *intSG = sig_cbL.createIntegral(RooArgSet(mBc), NormSet(mBc), Range("sigrance"));

//cout << "\n ##################### \n BG integral is " << Nbg.getVal()*intBG->getVal() << "+/-" << Nbg.getError()*intBG->getVal() << endl;
//cout << "\n Signal Integral is " << Nsig.getVal()*intSG->getVal() << "+/-" << Nsig.getError()*intSG->getVal() << endl;


















}
