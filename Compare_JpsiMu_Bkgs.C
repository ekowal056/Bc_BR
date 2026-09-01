////////////////////
///
/// Plot JpsiMu Simulation and other Background Simulations
///
///
/////////////////////////////


void Compare_JpsiMu_Bkgs(){


TFile *JpsiMuRoot = new TFile("Bc2JpsiMu_step1_sim18.root", "Read");
TTree *JpsiMu;
JpsiMu=dynamic_cast<TTree*>(JpsiMuRoot->Get("DecayTree"));
TH1D *JpsiMuHist_VisBc = new TH1D("JpsiMuHist_VisBc", "JpsiMu Visible Bc Mass", 100, 3000, 6500);
TH1D *JpsiMuHist_CorBc = new TH1D("JpsiMuHist_CorBc", "JpsiMu Corrected Bc Mass", 100, 3000, 10000);
TH1D *JpsiMuHist_VisCut = new TH1D("JpsiMuHist_VisCut", "Jpsi Mu Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *JpsiMuHist_CorCut = new TH1D("JpsiMuHist_CorCut", "JpsiMu Corrected Bc Mass >5300MeV", 100, 3000, 10000);


JpsiMu->Draw("Bc_M >> JpsiMuHist_VisBc", "", "goff") ;
JpsiMu->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>JpsiMuHist_CorBc", "", "goff");
JpsiMu->Draw("Bc_M >> JpsiMuHist_VisCut", "Bc_M>5300", "goff") ;
JpsiMu->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>JpsiMuHist_CorCut", "Bc_M>5300", "goff");


double JpsiMu_VisInt = JpsiMuHist_VisBc->Integral();
double JpsiMu_CorInt = JpsiMuHist_CorBc->Integral();
//double JpsiMu_VisEff = JpsiMuHist_VisCut->Integral()/JpsiMu_VisInt;
//double JpsiMu_CorEff = JpsiMuHist_CorCut->Integral()/JpsiMu_CorInt;

JpsiMuHist_VisBc->SetLineColor(kRed);
JpsiMuHist_CorBc->SetLineColor(kRed);
JpsiMuHist_VisBc->SetLineWidth(3);
JpsiMuHist_CorBc->SetLineWidth(3);

JpsiMuHist_VisCut->SetLineColor(kRed);
JpsiMuHist_CorCut->SetLineColor(kRed);
JpsiMuHist_VisCut->SetLineWidth(3);
JpsiMuHist_CorCut->SetLineWidth(3);

////////////////////////////

TFile *Psi2SMuRoot_e = new TFile("BKG_Step1/Bc2Psi2SMu_ebert_step1.root", "Read");
TTree *Psi2SMu_e;
Psi2SMu_e=dynamic_cast<TTree*>(Psi2SMuRoot_e->Get("DecayTree"));
TH1D *Psi2SMueHist_VisBc = new TH1D("Psi2SMueHist_VisBc", "Psi2S Mu Visible Bc Mass", 100, 3000, 6500);
TH1D *Psi2SMueHist_CorBc = new TH1D("Psi2SMueHist_CorBc", "Psi2S Mu Corrected Bc Mass", 100, 3000, 10000);
TH1D *Psi2SMueHist_VisCut = new TH1D("Psi2SMueHist_VisCut", "Psi2S Mu ebert Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *Psi2SMueHist_CorCut = new TH1D("Psi2SMueHist_CorCut", "Psi2S Mu ebert Corrected Bc Mass >5300MeV", 100, 3000, 10000);

Psi2SMu_e->Draw("Bc_M >> Psi2SMueHist_VisBc", "", "goff") ;
Psi2SMu_e->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Psi2SMueHist_CorBc", "", "goff");
Psi2SMu_e->Draw("Bc_M >> Psi2SMueHist_VisCut", "Bc_M >5300", "goff") ;
Psi2SMu_e->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Psi2SMueHist_CorCut", "Bc_M > 5300", "goff");

double Psi2SMue_VisInt = Psi2SMueHist_VisBc->Integral();
double Psi2SMue_CorInt = Psi2SMueHist_CorBc->Integral();
//double Psi2SMue_VisEff = Psi2SMueHist_VisCut->Integral()/ Psi2SMue_VisInt;
//double Psi2SMue_CorEff = Psi2SMueHist_CorCut->Integral()/ Psi2SMue_CorInt;

Psi2SMueHist_VisBc->Scale((260.0/8520.0)*(JpsiMu_VisInt / Psi2SMue_VisInt));
Psi2SMueHist_CorBc->Scale((260.0/8520.0)*(JpsiMu_CorInt / Psi2SMue_CorInt));
Psi2SMueHist_VisCut->Scale((260.0/8520.0)*(JpsiMu_VisInt / Psi2SMue_VisInt));//*(Psi2SMue_VisEff/JpsiMu_VisEff));
Psi2SMueHist_CorCut->Scale((260.0/8520.0)*(JpsiMu_CorInt / Psi2SMue_CorInt));//*(Psi2SMue_CorEff/JpsiMu_CorEff));


Psi2SMueHist_VisBc->SetLineColor(kBlue);
Psi2SMueHist_CorBc->SetLineColor(kBlue);
Psi2SMueHist_VisBc->SetLineWidth(3);
Psi2SMueHist_CorBc->SetLineWidth(3);

Psi2SMueHist_VisCut->SetLineColor(kBlue);
Psi2SMueHist_CorCut->SetLineColor(kBlue);
Psi2SMueHist_VisCut->SetLineWidth(3);
Psi2SMueHist_CorCut->SetLineWidth(3);

////////////////////////////////

TFile *Psi2SMuRoot_k = new TFile("BKG_Step1/Bc2Psi2SMu_kslv_step1.root", "Read");
TTree *Psi2SMu_k;
Psi2SMu_k=dynamic_cast<TTree*>(Psi2SMuRoot_k->Get("DecayTree"));
TH1D *Psi2SMukHist_VisBc = new TH1D("Psi2SMukHist_VisBc", "Psi2S Mu Visible Bc Mass", 100, 3000, 6500);
TH1D *Psi2SMukHist_CorBc = new TH1D("Psi2SMukHist_CorBc", "Psi2S Mu Corrected Bc Mass", 100, 3000, 10000);
TH1D *Psi2SMukHist_VisCut = new TH1D("Psi2SMukHist_VisCut", "Psi2S Mu kslv Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *Psi2SMukHist_CorCut = new TH1D("Psi2SMukHist_CorCut", "Psi2S Mu kslv Corrected Bc Mass >5300MeV", 100, 3000, 10000);

Psi2SMu_k->Draw("Bc_M >> Psi2SMukHist_VisBc", "", "goff") ;
Psi2SMu_k->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Psi2SMukHist_CorBc", "", "goff");
Psi2SMu_k->Draw("Bc_M >> Psi2SMukHist_VisCut", "Bc_M >5300", "goff") ;
Psi2SMu_k->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Psi2SMukHist_CorCut", "Bc_M > 5300", "goff");

double Psi2SMuk_VisInt = Psi2SMukHist_VisBc->Integral();
double Psi2SMuk_CorInt = Psi2SMukHist_CorBc->Integral();
//double Psi2SMuk_VisEff = Psi2SMukHist_VisCut->Integral()/ Psi2SMuk_VisInt;
//double Psi2SMuk_CorEff = Psi2SMukHist_CorCut->Integral()/ Psi2SMuk_CorInt;

Psi2SMukHist_VisBc->Scale((260.0/8520.0)*(JpsiMu_VisInt / Psi2SMuk_VisInt));
Psi2SMukHist_CorBc->Scale((260.0/8520.0)*(JpsiMu_CorInt / Psi2SMuk_CorInt));
Psi2SMukHist_VisCut->Scale((260.0/8520.0)*(JpsiMu_VisInt / Psi2SMuk_VisInt));//*(Psi2SMuk_VisEff/JpsiMu_VisEff));
Psi2SMukHist_CorCut->Scale((260.0/8520.0)*(JpsiMu_CorInt / Psi2SMuk_CorInt));//*(Psi2SMuk_CorEff/JpsiMu_CorEff));

Psi2SMukHist_VisBc->SetLineColor(kAzure-4);
Psi2SMukHist_CorBc->SetLineColor(kAzure-4);
Psi2SMukHist_VisBc->SetLineWidth(3);
Psi2SMukHist_CorBc->SetLineWidth(3);

Psi2SMukHist_VisCut->SetLineColor(kAzure-4);
Psi2SMukHist_CorCut->SetLineColor(kAzure-4);
Psi2SMukHist_VisCut->SetLineWidth(3);
Psi2SMukHist_CorCut->SetLineWidth(3);

//////////////////////////////////////////////////////

TFile *Chic1MuRoot = new TFile("BKG_Step1/Bc2Chic1Mu_step1.root", "Read");
TTree *Chic1Mu;
Chic1Mu=dynamic_cast<TTree*>(Chic1MuRoot->Get("DecayTree"));
TH1D *Chic1MuHist_VisBc = new TH1D("Chic1MuHist_VisBc", "Chic1 Mu Visible Bc Mass", 100, 3000, 6500);
TH1D *Chic1MuHist_CorBc = new TH1D("Chic1MuHist_CorBc", "Chic1 Mu Corrected Bc Mass", 100, 3000, 10000);
TH1D *Chic1MuHist_VisCut = new TH1D("Chic1MuHist_VisCut", "Chic1 Mu Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *Chic1MuHist_CorCut = new TH1D("Chic1MuHist_CorCut", "Chic1 Mu Corrected Bc Mass >5300MeV", 100, 3000, 10000);

Chic1Mu->Draw("Bc_M >> Chic1MuHist_VisBc", "", "goff") ;
Chic1Mu->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Chic1MuHist_CorBc", "", "goff");
Chic1Mu->Draw("Bc_M >> Chic1MuHist_VisCut", "Bc_M >5300", "goff") ;
Chic1Mu->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Chic1MuHist_CorCut", "Bc_M > 5300", "goff");

double Chic1Mu_VisInt = Chic1MuHist_VisBc->Integral();
double Chic1Mu_CorInt = Chic1MuHist_CorBc->Integral();
//double Chic1Mu_VisEff = Chic1MuHist_VisCut->Integral()/ Chic1Mu_VisInt;
//double Chic1Mu_CorEff = Chic1MuHist_CorCut->Integral()/ Chic1Mu_CorInt;

Chic1MuHist_VisBc->Scale((277.0/8520.0)*(JpsiMu_VisInt / Chic1Mu_VisInt));
Chic1MuHist_CorBc->Scale((277.0/8520.0)*(JpsiMu_CorInt / Chic1Mu_CorInt));
Chic1MuHist_VisCut->Scale((277.0/8520.0)*(JpsiMu_VisInt / Chic1Mu_VisInt));//*(Chic1Mu_VisEff/JpsiMu_VisEff));
Chic1MuHist_CorCut->Scale((277.0/8520.0)*(JpsiMu_CorInt / Chic1Mu_CorInt));//*(Chic1Mu_CorEff/JpsiMu_CorEff));


Chic1MuHist_VisBc->SetLineColor(kGreen);
Chic1MuHist_CorBc->SetLineColor(kGreen);
Chic1MuHist_VisBc->SetLineWidth(3);
Chic1MuHist_CorBc->SetLineWidth(3);

Chic1MuHist_VisCut->SetLineColor(kGreen);
Chic1MuHist_CorCut->SetLineColor(kGreen);
Chic1MuHist_VisCut->SetLineWidth(3);
Chic1MuHist_CorCut->SetLineWidth(3);

/////////////////////////////////////////////////////

TFile *Chic2MuRoot = new TFile("BKG_Step1/Bc2Chic2Mu_step1.root", "Read");
TTree *Chic2Mu;
Chic2Mu=dynamic_cast<TTree*>(Chic2MuRoot->Get("DecayTree"));
TH1D *Chic2MuHist_VisBc = new TH1D("Chic2MuHist_VisBc", "Chic2 Mu Visible Bc Mass", 100, 3000, 6500);
TH1D *Chic2MuHist_CorBc = new TH1D("Chic2MuHist_CorBc", "Chic2 Mu Corrected Bc Mass", 100, 3000, 10000);
TH1D *Chic2MuHist_VisCut = new TH1D("Chic2MuHist_VisCut", "Chic2 Mu Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *Chic2MuHist_CorCut = new TH1D("Chic2MuHist_CorCut", "Chic2 Mu Corrected Bc Mass >5300MeV", 100, 3000, 10000);

Chic2Mu->Draw("Bc_M >> Chic2MuHist_VisBc", "", "goff") ;
Chic2Mu->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Chic2MuHist_CorBc", "", "goff");
Chic2Mu->Draw("Bc_M >> Chic2MuHist_VisCut", "Bc_M >5300", "goff") ;
Chic2Mu->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Chic2MuHist_CorCut", "Bc_M > 5300", "goff");

double Chic2Mu_VisInt = Chic2MuHist_VisBc->Integral();
double Chic2Mu_CorInt = Chic2MuHist_CorBc->Integral();
//double Chic2Mu_VisEff = Chic2MuHist_VisCut->Integral()/ Chic2Mu_VisInt;
//double Chic2Mu_CorEff = Chic2MuHist_CorCut->Integral()/ Chic2Mu_CorInt;

Chic2MuHist_VisBc->Scale((277.0/8520.0)*(JpsiMu_VisInt / Chic2Mu_VisInt));
Chic2MuHist_CorBc->Scale((277.0/8520.0)*(JpsiMu_CorInt / Chic2Mu_CorInt));
Chic2MuHist_VisCut->Scale((277.0/8520.0)*(JpsiMu_VisInt / Chic2Mu_VisInt));//*(Chic2Mu_VisEff/JpsiMu_VisEff));
Chic2MuHist_CorCut->Scale((277.0/8520.0)*(JpsiMu_CorInt / Chic2Mu_CorInt));//*(Chic2Mu_CorEff/JpsiMu_CorEff));

Chic2MuHist_VisBc->SetLineColor(kGreen+3);
Chic2MuHist_CorBc->SetLineColor(kGreen+3);
Chic2MuHist_VisBc->SetLineWidth(3);
Chic2MuHist_CorBc->SetLineWidth(3);

Chic2MuHist_VisCut->SetLineColor(kGreen+3);
Chic2MuHist_CorCut->SetLineColor(kGreen+3);
Chic2MuHist_VisCut->SetLineWidth(3);
Chic2MuHist_CorCut->SetLineWidth(3);

/////////////////////////////////////////////////////////

TFile *Psi2STaueRoot = new TFile("BKG_Step1/Bc2Psi2STau_ebert_step1.root", "Read");
TTree *Psi2STaue;
Psi2STaue=dynamic_cast<TTree*>(Psi2STaueRoot->Get("DecayTree"));
TH1D *Psi2STaueHist_VisBc = new TH1D("Psi2STaueHist_VisBc", "Psi2S Tau e Visible Bc Mass", 100, 3000, 6500);
TH1D *Psi2STaueHist_CorBc = new TH1D("Psi2STaueHist_CorBc", "Psi2S Tau e Corrected Bc Mass", 100, 3000, 10000);
TH1D *Psi2STaueHist_VisCut = new TH1D("Psi2STaueHist_VisCut", "Psi2S Tau ebert Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *Psi2STaueHist_CorCut = new TH1D("Psi2STaueHist_CorCut", "Psi2S Tau ebert Corrected Bc Mass >5300MeV", 100, 3000, 10000);

Psi2STaue->Draw("Bc_M >> Psi2STaueHist_VisBc", "", "goff") ;
Psi2STaue->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> Psi2STaueHist_CorBc", "", "goff");
Psi2STaue->Draw("Bc_M >> Psi2STaueHist_VisCut", "Bc_M >5300", "goff") ;
Psi2STaue->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Psi2STaueHist_CorCut", "Bc_M > 5300", "goff");

double Psi2STaue_VisInt = Psi2STaueHist_VisBc->Integral();
double Psi2STaue_CorInt = Psi2STaueHist_CorBc->Integral();
//double Psi2STaue_VisEff = Psi2STaueHist_VisCut->Integral()/ Psi2STaue_VisInt;
//double Psi2STaue_CorEff = Psi2STaueHist_CorCut->Integral()/ Psi2STaue_CorInt;

Psi2STaueHist_VisBc->Scale((2.0/8520.0)*(JpsiMu_VisInt / Psi2STaue_VisInt));
Psi2STaueHist_CorBc->Scale((2.0/8520.0)*(JpsiMu_CorInt / Psi2STaue_CorInt));
Psi2STaueHist_VisCut->Scale((2.0/8520.0)*(JpsiMu_VisInt / Psi2STaue_VisInt));//*(Psi2STaue_VisEff/JpsiMu_VisEff));
Psi2STaueHist_CorCut->Scale((2.0/8520.0)*(JpsiMu_CorInt / Psi2STaue_CorInt));//*(Psi2STaue_CorEff/JpsiMu_CorEff));

Psi2STaueHist_VisBc->SetLineColor(kCyan);
Psi2STaueHist_CorBc->SetLineColor(kCyan);
Psi2STaueHist_VisBc->SetLineWidth(3);
Psi2STaueHist_CorBc->SetLineWidth(3);

Psi2STaueHist_VisCut->SetLineColor(kCyan);
Psi2STaueHist_CorCut->SetLineColor(kCyan);
Psi2STaueHist_VisCut->SetLineWidth(3);
Psi2STaueHist_CorCut->SetLineWidth(3);

/////////////////////////////////////////////////////

TFile *Psi2STaukRoot = new TFile("BKG_Step1/Bc2Psi2STau_kslv_step1.root", "Read");
TTree *Psi2STauk;
Psi2STauk=dynamic_cast<TTree*>(Psi2STaukRoot->Get("DecayTree"));
TH1D *Psi2STaukHist_VisBc = new TH1D("Psi2STaukHist_VisBc", "Psi2S Tau k Visible Bc Mass", 100, 3000, 6500);
TH1D *Psi2STaukHist_CorBc = new TH1D("Psi2STaukHist_CorBc", "Psi2S Tau k Corrected Bc Mass", 100, 3000, 10000);
TH1D *Psi2STaukHist_VisCut = new TH1D("Psi2STaukHist_VisCut", "Psi2S Tau k Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *Psi2STaukHist_CorCut = new TH1D("Psi2STaukHist_CorCut", "Psi2S Tau k Corrected Bc Mass >5300MeV", 100, 3000, 10000);

Psi2STauk->Draw("Bc_M >> Psi2STaukHist_VisBc", "", "goff") ;
Psi2STauk->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> Psi2STaukHist_CorBc", "", "goff");
Psi2STauk->Draw("Bc_M >> Psi2STaukHist_VisCut", "Bc_M >5300", "goff") ;
Psi2STauk->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> Psi2STaukHist_CorCut", "Bc_M > 5300", "goff");

double Psi2STauk_VisInt = Psi2STaukHist_VisBc->Integral();
double Psi2STauk_CorInt = Psi2STaukHist_CorBc->Integral();
//double Psi2STauk_VisEff = Psi2STaukHist_VisCut->Integral()/ Psi2STauk_VisInt;
//double Psi2STauk_CorEff = Psi2STaukHist_CorCut->Integral()/ Psi2STauk_CorInt;

Psi2STaukHist_VisBc->Scale((2.0/8520.0)*(JpsiMu_VisInt / Psi2STauk_VisInt));
Psi2STaukHist_CorBc->Scale((2.0/8520.0)*(JpsiMu_CorInt / Psi2STauk_CorInt));
Psi2STaukHist_VisCut->Scale((2.0/8520.0)*(JpsiMu_VisInt / Psi2STauk_VisInt));//*(Psi2STauk_VisEff/JpsiMu_VisEff));
Psi2STaukHist_CorCut->Scale((2.0/8520.0)*(JpsiMu_CorInt / Psi2STauk_CorInt));//*(Psi2STauk_CorEff/JpsiMu_CorEff));

Psi2STaukHist_VisBc->SetLineColor(kCyan-6);
Psi2STaukHist_CorBc->SetLineColor(kCyan-6);
Psi2STaukHist_VisBc->SetLineWidth(3);
Psi2STaukHist_CorBc->SetLineWidth(3);

Psi2STaukHist_VisCut->SetLineColor(kCyan-6);
Psi2STaukHist_CorCut->SetLineColor(kCyan-6);
Psi2STaukHist_VisCut->SetLineWidth(3);
Psi2STaukHist_CorCut->SetLineWidth(3);

///////////////////////////////////////////////////////

TFile *JpsiDRoot = new TFile("BKG_Step1/Bc2JpsiD_step1.root", "Read");
TTree *JpsiD;
JpsiD=dynamic_cast<TTree*>(JpsiDRoot->Get("DecayTree"));
TH1D *JpsiDHist_VisBc = new TH1D("JpsiDHist_VisBc", "Jpsi D Visible Bc Mass", 100, 3000, 6500);
TH1D *JpsiDHist_CorBc = new TH1D("JpsiDHist_CorBc", "Jpsi D Corrected Bc Mass", 100, 3000, 10000);
TH1D *JpsiDHist_VisCut = new TH1D("JpsiDHist_VisCut", "Jpsi D Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *JpsiDHist_CorCut = new TH1D("JpsiDHist_CorCut", "Jpsi D Corrected Bc Mass >5300MeV", 100, 3000, 10000);


JpsiD->Draw("Bc_M >> JpsiDHist_VisBc", "", "goff") ;
JpsiD->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> JpsiDHist_CorBc", "", "goff");
JpsiD->Draw("Bc_M >> JpsiDHist_VisCut", "Bc_M >5300", "goff") ;
JpsiD->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> JpsiDHist_CorCut", "Bc_M > 5300", "goff");

double JpsiD_VisInt = JpsiDHist_VisBc->Integral();
double JpsiD_CorInt = JpsiDHist_CorBc->Integral();
//double JpsiD_VisEff = JpsiDHist_VisCut->Integral()/ JpsiD_VisInt;
//double JpsiD_CorEff = JpsiDHist_CorCut->Integral()/ JpsiD_CorInt;

JpsiDHist_VisBc->Scale((55.0/8520.0)*(JpsiMu_VisInt / JpsiD_VisInt));
JpsiDHist_CorBc->Scale((55.0/8520.0)*(JpsiMu_CorInt / JpsiD_CorInt));
JpsiDHist_VisCut->Scale((55.0/8520.0)*(JpsiMu_VisInt / JpsiD_VisInt));//*(JpsiD_VisEff/JpsiMu_VisEff));
JpsiDHist_CorCut->Scale((55.0/8520.0)*(JpsiMu_CorInt / JpsiD_CorInt));//*(JpsiD_CorEff/JpsiMu_CorEff));

JpsiDHist_VisBc->SetLineColor(kViolet);
JpsiDHist_CorBc->SetLineColor(kViolet);
JpsiDHist_VisBc->SetLineWidth(3);
JpsiDHist_CorBc->SetLineWidth(3);

JpsiDHist_VisCut->SetLineColor(kViolet);
JpsiDHist_CorCut->SetLineColor(kViolet);
JpsiDHist_VisCut->SetLineWidth(3);
JpsiDHist_CorCut->SetLineWidth(3);

///////////////////////////////////////////////////////

TFile *JpsiDKRoot = new TFile("BKG_Step1/Bc2JpsiDK_step1.root", "Read");
TTree *JpsiDK;
JpsiDK=dynamic_cast<TTree*>(JpsiDKRoot->Get("DecayTree"));
TH1D *JpsiDKHist_VisBc = new TH1D("JpsiDKHist_VisBc", "Jpsi D K Visible Bc Mass", 100, 3000, 6500);
TH1D *JpsiDKHist_CorBc = new TH1D("JpsiDKHist_CorBc", "Jpsi D K Corrected Bc Mass", 100, 3000, 10000);
TH1D *JpsiDKHist_VisCut = new TH1D("JpsiDKHist_VisCut", "Jpsi D K Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *JpsiDKHist_CorCut = new TH1D("JpsiDKHist_CorCut", "Jpsi D K Corrected Bc Mass >5300MeV", 100, 3000, 10000);

JpsiDK->Draw("Bc_M >> JpsiDKHist_VisBc", "", "goff") ;
JpsiDK->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> JpsiDKHist_CorBc", "", "goff");
JpsiDK->Draw("Bc_M >> JpsiDKHist_VisCut", "Bc_M >5300", "goff") ;
JpsiDK->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>JpsiDKHist_CorCut", "Bc_M > 5300", "goff");

double JpsiDK_VisInt = JpsiDKHist_VisBc->Integral();
double JpsiDK_CorInt = JpsiDKHist_CorBc->Integral();
//double JpsiDK_VisEff = JpsiDKHist_VisCut->Integral()/ JpsiDK_VisInt;
//double JpsiDK_CorEff = JpsiDKHist_CorCut->Integral()/ JpsiDK_CorInt;

JpsiDKHist_VisBc->Scale((5.0/8520.0)*(JpsiMu_VisInt / JpsiDK_VisInt));
JpsiDKHist_CorBc->Scale((5.0/8520.0)*(JpsiMu_CorInt / JpsiDK_CorInt));
JpsiDKHist_VisCut->Scale((5.0/8520.0)*(JpsiMu_VisInt / JpsiDK_VisInt));//*(JpsiDK_VisEff/JpsiMu_VisEff));
JpsiDKHist_CorCut->Scale((5.0/8520.0)*(JpsiMu_CorInt / JpsiDK_CorInt));//*(JpsiDK_CorEff/JpsiMu_CorEff));

JpsiDKHist_VisBc->SetLineColor(kViolet+1);
JpsiDKHist_CorBc->SetLineColor(kViolet+1);
JpsiDKHist_VisBc->SetLineWidth(3);
JpsiDKHist_CorBc->SetLineWidth(3);

JpsiDKHist_VisCut->SetLineColor(kViolet+1);
JpsiDKHist_CorCut->SetLineColor(kViolet+1);
JpsiDKHist_VisCut->SetLineWidth(3);
JpsiDKHist_CorCut->SetLineWidth(3);

////////////////////////////////////////////////////////

TFile *JpsiDststRoot = new TFile("BKG_Step1/Bc2JpsiDstst_step1.root", "Read");
TTree *JpsiDstst;
JpsiDstst=dynamic_cast<TTree*>(JpsiDststRoot->Get("DecayTree"));
TH1D *JpsiDststHist_VisBc = new TH1D("JpsiDststHist_VisBc", " Visible Bc Mass", 100, 3000, 6500);
TH1D *JpsiDststHist_CorBc = new TH1D("JpsiDststHist_CorBc", " Corrected Bc Mass", 100, 3000, 10000);
TH1D *JpsiDststHist_VisCut = new TH1D("JpsiDststHist_VisCut", "Jpsi Dstst Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *JpsiDststHist_CorCut = new TH1D("JpsiDststHist_CorCut", "Jpsi Dstst Corrected Bc Mass >5300MeV", 100, 3000, 10000);

JpsiDstst->Draw("Bc_M >> JpsiDststHist_VisBc", "", "goff");
JpsiDstst->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> JpsiDststHist_CorBc", "", "goff");
JpsiDstst->Draw("Bc_M >> JpsiDststHist_VisCut", "Bc_M >5300", "goff");
JpsiDstst->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>JpsiDststHist_CorCut", "Bc_M > 5300", "goff");

double JpsiDstst_VisInt = JpsiDststHist_VisBc->Integral();
double JpsiDstst_CorInt = JpsiDststHist_CorBc->Integral();
//double JpsiDstst_VisEff = JpsiDststHist_VisCut->Integral()/ JpsiDstst_VisInt;
//double JpsiDstst_CorEff = JpsiDststHist_CorCut->Integral()/ JpsiDstst_CorInt;

JpsiDststHist_VisBc->Scale((17.0/8520.0)*(JpsiMu_VisInt / JpsiDstst_VisInt));
JpsiDststHist_CorBc->Scale((17.0/8520.0)*(JpsiMu_CorInt / JpsiDstst_CorInt));
JpsiDststHist_VisCut->Scale((17.0/8520.0)*(JpsiMu_VisInt / JpsiDstst_VisInt));//*(JpsiDstst_VisEff/JpsiMu_VisEff));
JpsiDststHist_CorCut->Scale((17.0/8520.0)*(JpsiMu_CorInt / JpsiDstst_CorInt));//*(JpsiDstst_CorEff/JpsiMu_CorEff));

JpsiDststHist_VisBc->SetLineColor(kViolet+7);
JpsiDststHist_CorBc->SetLineColor(kViolet+7);
JpsiDststHist_VisBc->SetLineWidth(3);
JpsiDststHist_CorBc->SetLineWidth(3);

/////////////////////////////////////////////////////

TFile *JpsiTauRoot = new TFile("BKG_Step1/Bc2JpsiTau_step1.root", "Read");
TTree *JpsiTau;
JpsiTau=dynamic_cast<TTree*>(JpsiTauRoot->Get("DecayTree"));
TH1D *JpsiTauHist_VisBc = new TH1D("JpsiTauHist_VisBc", "Jpsi Tau Visible Bc Mass", 100, 3000, 6500);
TH1D *JpsiTauHist_CorBc = new TH1D("JpsiTauHist_CorBc", "Jpsi Tau Corrected Bc Mass", 100, 3000, 10000);
TH1D *JpsiTauHist_VisCut = new TH1D("JpsiTauHist_VisCut", "Jpsi Tau Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *JpsiTauHist_CorCut = new TH1D("JpsiTauHist_CorCut", "Jpsi Tau Corrected Bc Mass >5300MeV", 100, 3000, 10000);


JpsiTau->Draw("Bc_M >> JpsiTauHist_VisBc", "", "goff") ;
JpsiTau->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> JpsiTauHist_CorBc", "", "goff");
JpsiTau->Draw("Bc_M >> JpsiTauHist_VisCut", "Bc_M >5300", "goff") ;
JpsiTau->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> JpsiTauHist_CorCut", "Bc_M > 5300", "goff");

double JpsiTau_VisInt = JpsiTauHist_VisBc->Integral();
double JpsiTau_CorInt = JpsiTauHist_CorBc->Integral();
//double JpsiTau_VisEff = JpsiTauHist_VisCut->Integral()/ JpsiTau_VisInt;
//double JpsiTau_CorEff = JpsiTauHist_CorCut->Integral()/ JpsiTau_CorInt;

JpsiTauHist_VisBc->Scale((426.0/8520.0)*(JpsiMu_VisInt / JpsiTau_VisInt));
JpsiTauHist_CorBc->Scale((426.0/8520.0)*(JpsiMu_CorInt / JpsiTau_CorInt));
JpsiTauHist_VisCut->Scale((426.0/8520.0)*(JpsiMu_VisInt / JpsiTau_VisInt));//*(JpsiTau_VisEff/JpsiMu_VisEff));
JpsiTauHist_CorCut->Scale((426.0/8520.0)*(JpsiMu_CorInt / JpsiTau_CorInt));//*(JpsiTau_CorEff/JpsiMu_CorEff));

JpsiTauHist_VisBc->SetLineColor(kOrange);
JpsiTauHist_CorBc->SetLineColor(kOrange);
JpsiTauHist_VisBc->SetLineWidth(3);
JpsiTauHist_CorBc->SetLineWidth(3);

JpsiTauHist_VisCut->SetLineColor(kOrange);
JpsiTauHist_CorCut->SetLineColor(kOrange);
JpsiTauHist_VisCut->SetLineWidth(3);
JpsiTauHist_CorCut->SetLineWidth(3);

////////////////////////////////////////////////////

TFile *Bud2JpsiXRoot = new TFile("BKG_Step1/Bd2JpsiX_step1.root", "Read");
TTree *Bud2JpsiX;
Bud2JpsiX=dynamic_cast<TTree*>(Bud2JpsiXRoot->Get("DecayTree"));
TH1D *Bud2JpsiXHist_VisBc = new TH1D("Bud2JpsiXHist_VisBc", " Visible Bc Mass", 100, 3000, 6500);
TH1D *Bud2JpsiXHist_CorBc = new TH1D("Bud2JpsiXHist_CorBc", " Corrected Bc Mass", 100, 3000, 10000);
TH1D *Bud2JpsiXHist_VisCut = new TH1D("Bud2JpsiXHist_VisCut", "Bud to Jpsi X Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *Bud2JpsiXHist_CorCut = new TH1D("Bud2JpsiXHist_CorCut", "Bud to Jpsi X Corrected Bc Mass >5300MeV", 100, 3000, 10000);

Bud2JpsiX->Draw("Bc_M >> Bud2JpsiXHist_VisBc", "", "goff") ;
Bud2JpsiX->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> Bud2JpsiXHist_CorBc", "", "goff");
Bud2JpsiX->Draw("Bc_M >> Bud2JpsiXHist_VisCut", "Bc_M >5300", "goff") ;
Bud2JpsiX->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>>Bud2JpsiXHist_CorCut", "Bc_M > 5300", "goff");

double Bud2JpsiX_VisInt = Bud2JpsiXHist_VisBc->Integral();
double Bud2JpsiX_CorInt = Bud2JpsiXHist_CorBc->Integral();
//double Bud2JpsiX_VisEff = Bud2JpsiXHist_VisCut->Integral()/ Bud2JpsiX_VisInt;
//double Bud2JpsiX_CorEff = Bud2JpsiXHist_CorCut->Integral()/ Bud2JpsiX_CorInt;

Bud2JpsiXHist_VisBc->Scale((87.0/8520.0)*(JpsiMu_VisInt / Bud2JpsiX_VisInt));
Bud2JpsiXHist_CorBc->Scale((87.0/8520.0)*(JpsiMu_CorInt / Bud2JpsiX_CorInt));
Bud2JpsiXHist_VisCut->Scale((87.0/8520.0)*(JpsiMu_VisInt / Bud2JpsiX_VisInt));//*(Bud2JpsiX_VisEff/JpsiMu_VisEff));
Bud2JpsiXHist_CorCut->Scale((87.0/8520.0)*(JpsiMu_CorInt / Bud2JpsiX_CorInt));//*(Bud2JpsiX_CorEff/JpsiMu_CorEff));

Bud2JpsiXHist_VisBc->SetLineColor(kOrange+7);
Bud2JpsiXHist_CorBc->SetLineColor(kOrange+7);
Bud2JpsiXHist_VisBc->SetLineWidth(3);
Bud2JpsiXHist_CorBc->SetLineWidth(3);

Bud2JpsiXHist_VisCut->SetLineColor(kOrange+7);
Bud2JpsiXHist_CorCut->SetLineColor(kOrange+7);
Bud2JpsiXHist_VisCut->SetLineWidth(3);
Bud2JpsiXHist_CorCut->SetLineWidth(3);

/////////////////////////////////////////////////////////

TFile *Bs2JpsiXRoot = new TFile("BKG_Step1/Bs2JpsiX_step1.root", "Read");
TTree *Bs2JpsiX;
Bs2JpsiX=dynamic_cast<TTree*>(Bs2JpsiXRoot->Get("DecayTree"));
TH1D *Bs2JpsiXHist_VisBc = new TH1D("Bs2JpsiXHist_VisBc", " Visible Bc Mass", 100, 3000, 6500);
TH1D *Bs2JpsiXHist_CorBc = new TH1D("Bs2JpsiXHist_CorBc", " Corrected Bc Mass", 100, 3000, 10000);
TH1D *Bs2JpsiXHist_VisCut = new TH1D("Bs2JpsiXHist_VisCut", "Bs2JpsiX Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *Bs2JpsiXHist_CorCut = new TH1D("Bs2JpsiXHist_CorCut", "Bs2JpsiX Corrected Bc Mass >5300MeV", 100, 3000, 10000);


Bs2JpsiX->Draw("Bc_M >> Bs2JpsiXHist_VisBc", "", "goff") ;
Bs2JpsiX->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> Bs2JpsiXHist_CorBc", "", "goff");
Bs2JpsiX->Draw("Bc_M >> Bs2JpsiXHist_VisCut", "Bc_M >5300", "goff") ;
Bs2JpsiX->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> Bs2JpsiXHist_CorCut", "Bc_M > 5300", "goff");

double Bs2JpsiX_VisInt = Bs2JpsiXHist_VisBc->Integral();
double Bs2JpsiX_CorInt = Bs2JpsiXHist_CorBc->Integral();
//double Bs2JpsiX_VisEff = Bs2JpsiXHist_VisCut->Integral()/ Bs2JpsiX_VisInt;
//double Bs2JpsiX_CorEff = Bs2JpsiXHist_CorCut->Integral()/ Bs2JpsiX_CorInt;

Bs2JpsiXHist_VisBc->Scale((10.0/8520.0)*(JpsiMu_VisInt / Bs2JpsiX_VisInt));
Bs2JpsiXHist_CorBc->Scale((10.0/8520.0)*(JpsiMu_CorInt / Bs2JpsiX_CorInt));
Bs2JpsiXHist_VisCut->Scale((10.0/8520.0)*(JpsiMu_VisInt / Bs2JpsiX_VisInt));//*(Bs2JpsiX_VisEff/JpsiMu_VisEff));
Bs2JpsiXHist_CorCut->Scale((10.0/8520.0)*(JpsiMu_CorInt / Bs2JpsiX_CorInt));//*(Bs2JpsiX_CorEff/JpsiMu_CorEff));

Bs2JpsiXHist_VisBc->SetLineColor(kOrange-3);
Bs2JpsiXHist_CorBc->SetLineColor(kOrange-3);
Bs2JpsiXHist_VisBc->SetLineWidth(3);
Bs2JpsiXHist_CorBc->SetLineWidth(3);

Bs2JpsiXHist_VisCut->SetLineColor(kOrange-3);
Bs2JpsiXHist_CorCut->SetLineColor(kOrange-3);
Bs2JpsiXHist_VisCut->SetLineWidth(3);
Bs2JpsiXHist_CorCut->SetLineWidth(3);

/////////////////////////////////////////////////////

TFile *misID_MDRoot = new TFile("BKG_Step1/2018_Data_MD_misID_Mcut_prescale_step1.root", "Read");
TTree *misID_MD;
misID_MD=dynamic_cast<TTree*>(misID_MDRoot->Get("DecayTree"));

TFile *misID_MURoot = new TFile("BKG_Step1/2018_Data_MU_misID_Mcut_prescale_step1.root", "Read");
TTree *misID_MU;
misID_MU=dynamic_cast<TTree*>(misID_MURoot->Get("DecayTree"));

TH1D *misIDHist_VisBc = new TH1D("misIDHist_VisBc", " Visible Bc Mass", 100, 3000, 6500);
TH1D *misIDHist_CorBc = new TH1D("misIDHist_CorBc", " Corrected Bc Mass", 100, 3000, 10000);
TH1D *misIDHist_VisCut = new TH1D("misIDHist_VisCut", " Visible Bc Mass >5300MeV", 100, 3000, 6500);
TH1D *misIDHist_CorCut = new TH1D("misIDHist_CorCut", " Corrected Bc Mass >5300MeV", 100, 3000, 10000);


misID_MU->Draw("Bc_M >> misIDHist_VisBc", "", "goff") ;
misID_MU->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> misIDHist_CorBc", "", "goff");
misID_MU->Draw("Bc_M >> misIDHist_VisCut", "Bc_M >5300", "goff") ;
misID_MU->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> misIDHist_CorCut", "Bc_M > 5300", "goff");

misID_MD->Draw("Bc_M >> +misIDHist_VisBc", "", "goff") ;
misID_MD->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> +misIDHist_CorBc", "", "goff");
misID_MD->Draw("Bc_M >> +misIDHist_VisCut", "Bc_M >5300", "goff") ;
misID_MD->Draw("(sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV))>> +misIDHist_CorCut", "Bc_M > 5300", "goff");

double misID_VisInt = misIDHist_VisBc->Integral();
double misID_CorInt = misIDHist_CorBc->Integral();

misIDHist_VisBc->Scale((2074.0/8520.0)*(JpsiMu_VisInt / misID_VisInt));
misIDHist_CorBc->Scale((2074.0/8520.0)*(JpsiMu_CorInt / misID_CorInt));
misIDHist_VisCut->Scale((2074.0/8520.0)*(JpsiMu_VisInt / misID_VisInt));//*(Bs2JpsiX_VisEff/JpsiMu_VisEff));
misIDHist_CorCut->Scale((2074.0/8520.0)*(JpsiMu_CorInt / misID_CorInt));//*(Bs2JpsiX_CorEff/JpsiMu_CorEff));


misIDHist_VisBc->SetLineColor(kBlack);
misIDHist_CorBc->SetLineColor(kBlack);
misIDHist_VisBc->SetLineWidth(3);
misIDHist_CorBc->SetLineWidth(3);

misIDHist_VisCut->SetLineColor(kBlack);
misIDHist_CorCut->SetLineColor(kBlack);
misIDHist_VisCut->SetLineWidth(3);
misIDHist_CorCut->SetLineWidth(3);

///////////////////////////////////////////////////////

gStyle->SetOptStat(0);

TCanvas *c1 = new TCanvas("c1", "c1", 480, 600);
c1->Divide(1,2);

TPad *overlay = new TPad("overlay","overlay",
                         0.0, 0.0, 1.0, 1.0);
overlay->SetFillStyle(4000);   // transparent
overlay->SetFrameFillStyle(4000);
overlay->Draw();
overlay->cd();

TLegend *leg = new TLegend(0.7, 0.75, 0.9, 0.9);
leg->AddEntry(JpsiMuHist_CorBc, "Jpsi Mu", "l");
leg->AddEntry(Psi2SMueHist_CorBc, "Psi(2S) Mu ebert", "l");
leg->AddEntry(Psi2SMukHist_CorBc, "Psi(2S) Mu kslv", "l");
leg->AddEntry(Psi2STaueHist_CorBc ,"Psi(2S) Tau ebert", "l");
leg->AddEntry(Psi2STaukHist_CorBc ,"Psi(2S) Tau kslv", "l");
leg->AddEntry(Chic1MuHist_CorBc, "Chi_{c1} Mu", "l");
leg->AddEntry(Chic2MuHist_CorBc, "Chi_{c2} Mu", "l");
leg->AddEntry(JpsiDHist_CorBc, "Jpsi D", "l");
leg->AddEntry(JpsiDKHist_CorBc, "Jpsi D K", "l");
leg->AddEntry(JpsiDststHist_CorBc, "Jpsi Dstst", "l");
leg->AddEntry(JpsiTauHist_CorBc , "Jpsi Tau", "l");
leg->AddEntry(Bud2JpsiXHist_CorBc , "B_{u,d} to Jpsi X", "l");
leg->AddEntry(Bs2JpsiXHist_CorBc , "B_{s} to Jpsi X", "l");
leg->AddEntry(misIDHist_CorBc, "misID", "l");
leg->Draw();


c1->cd (1);
gPad->SetName("top_plot");
gPad->SetTitle("B_C Visible Mass");
//gPad->SetLogy();
JpsiMuHist_VisBc->Draw("hist");
Psi2SMueHist_VisBc->Draw("hist same");
Psi2SMukHist_VisBc->Draw("hist same");
Chic1MuHist_VisBc->Draw("hist same");
Chic2MuHist_VisBc->Draw("hist same");
Psi2STaueHist_VisBc->Draw("hist same");
Psi2STaukHist_VisBc->Draw("hist same");
JpsiDHist_VisBc->Draw("hist same");
JpsiDKHist_VisBc->Draw("hist same");
JpsiDststHist_VisBc->Draw("hist same");
JpsiTauHist_VisBc->Draw("hist same");
Bud2JpsiXHist_VisBc->Draw("hist same");
Bs2JpsiXHist_VisBc->Draw("hist same");
misIDHist_VisBc->Draw("hist same");
JpsiMuHist_VisBc->GetXaxis()->SetTitle("M(B_{c}) [MeV]");
gPad->Update();

c1->cd(2);
//gPad->SetLogy();
JpsiMuHist_CorBc->Draw("hist");
JpsiMuHist_CorBc->GetXaxis()->SetTitle("M(B_{c}) [MeV]");
Psi2SMueHist_CorBc->Draw("hist same");
Psi2SMukHist_CorBc->Draw("hist same");
Chic1MuHist_CorBc->Draw("hist same");
Chic2MuHist_CorBc->Draw("hist same");
Psi2STaueHist_CorBc->Draw("hist same");
Psi2STaukHist_CorBc->Draw("hist same");
JpsiDHist_CorBc->Draw("hist same");
JpsiDKHist_CorBc->Draw("hist same");
JpsiDststHist_CorBc->Draw("hist same");
JpsiTauHist_CorBc->Draw("hist same");
Bud2JpsiXHist_CorBc->Draw("hist same");
Bs2JpsiXHist_CorBc->Draw("hist same");
misIDHist_CorBc->Draw("hist same");
gPad->SetName("bottom_plot");
gPad->SetTitle("B_C Corrected Mass");
gPad->Update();


TCanvas *c2 = new TCanvas("c2", "c2", 480, 600);
c2->Divide(1,2);

TPad *overlay2 = new TPad("overlay2","overlay2",
                         0.0, 0.0, 1.0, 1.0);
overlay2->SetFillStyle(4000);   // transparent
overlay2->SetFrameFillStyle(4000);
overlay2->Draw();
overlay2->cd();

TLegend *leg2 = new TLegend(0.7, 0.75, 0.9, 0.9);
leg2->AddEntry(JpsiMuHist_CorBc, "Jpsi Mu", "l");
leg2->AddEntry(Psi2SMueHist_CorBc, "Psi(2S) Mu ebert", "l");
leg2->AddEntry(Psi2SMukHist_CorBc, "Psi(2S) Mu kslv", "l");
leg2->AddEntry(Psi2STaueHist_CorBc ,"Psi(2S) Tau ebert", "l");
leg2->AddEntry(Psi2STaukHist_CorBc ,"Psi(2S) Tau kslv", "l");
leg2->AddEntry(Chic1MuHist_CorBc, "Chi_{c1} Mu", "l");
leg2->AddEntry(Chic2MuHist_CorBc, "Chi_{c2} Mu", "l");
leg2->AddEntry(JpsiDHist_CorBc, "Jpsi D", "l");
leg2->AddEntry(JpsiDKHist_CorBc, "Jpsi D K", "l");
leg2->AddEntry(JpsiDststHist_CorBc, "Jpsi Dstst", "l");
leg2->AddEntry(JpsiTauHist_CorBc , "Jpsi Tau", "l");
leg2->AddEntry(Bud2JpsiXHist_CorBc , "B_{u,d} to Jpsi X", "l");
leg2->AddEntry(Bs2JpsiXHist_CorBc , "B_{s} to Jpsi X", "l");
leg2->AddEntry(misIDHist_CorBc, "misID", "l");
leg2->Draw();

c2->cd (1);
JpsiMuHist_VisCut->Draw("hist");
Psi2SMueHist_VisCut->Draw("hist same");
Psi2SMukHist_VisCut->Draw("hist same");
Chic1MuHist_VisCut->Draw("hist same");
Chic2MuHist_VisCut->Draw("hist same");
Psi2STaueHist_VisCut->Draw("hist same");
Psi2STaukHist_VisCut->Draw("hist same");
JpsiDHist_VisCut->Draw("hist same");
JpsiDKHist_VisCut->Draw("hist same");
JpsiDststHist_VisCut->Draw("hist same");
JpsiTauHist_VisCut->Draw("hist same");
Bud2JpsiXHist_VisCut->Draw("hist same");
Bs2JpsiXHist_VisCut->Draw("hist same");
misIDHist_VisCut->Draw("hist same");

JpsiMuHist_VisCut->GetXaxis()->SetTitle("M(B_{c}) [MeV]");
JpsiMuHist_VisCut->GetXaxis()->SetRangeUser(5300, 6500);
JpsiMuHist_VisCut->GetYaxis()->SetRangeUser(1, 20000);

gPad->SetName("top_plot");
gPad->SetTitle("B_C Visible Mass");
//gPad->SetLogy();
gPad->Update();

c2->cd(2);
JpsiMuHist_CorCut->Draw("hist");
Psi2SMueHist_CorCut->Draw("hist same");
Psi2SMukHist_CorCut->Draw("hist same");
Chic1MuHist_CorCut->Draw("hist same");
Chic2MuHist_CorCut->Draw("hist same");
Psi2STaueHist_CorCut->Draw("hist same");
Psi2STaukHist_CorCut->Draw("hist same");
JpsiDHist_CorCut->Draw("hist same");
JpsiDKHist_CorCut->Draw("hist same");
JpsiDststHist_CorCut->Draw("hist same");
JpsiTauHist_CorCut->Draw("hist same");
Bud2JpsiXHist_CorCut->Draw("hist same");
Bs2JpsiXHist_CorCut->Draw("hist same");
misIDHist_CorCut->Draw("hist same");


JpsiMuHist_CorCut->GetXaxis()->SetTitle("M(B_{c}) [MeV]");
JpsiMuHist_CorCut->GetXaxis()->SetRangeUser(5200, 10000);
JpsiMuHist_CorCut->GetYaxis()->SetRangeUser(1, 20000);

gPad->SetName("bottom_plot");
gPad->SetTitle("B_C Corrected Mass");
//gPad->SetLogy();
gPad->Update();

}
