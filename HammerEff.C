void HammerEff()

{

  const int numWeights=31;

  TString parentDir="";

  TFile fin(parentDir+"Bc2JpsiMu_step1_sim18.root","READ");

  TTree *tin;

  fin.GetObject("DecayTree",tin);



  Double_t weights[numWeights];

  Double_t Mvis;



  ULong64_t eventNumber;

  UInt_t runNumber;

  Int_t eventNumberHam,runNumberHam;



  Double_t sumW[numWeights]; //to hold sum of weights for all events

  Double_t sumWpass[numWeights]; //to hold sum of weights for passed events

  Double_t sumW2[numWeights]; // to hold sum of weights squared if needed




  TFile f2in(parentDir+"MuWeights_new.root","READ");

  TTree *tham;

  f2in.GetObject("Hammer",tham);



  TString weightsToTest[numWeights];

  weightsToTest[0]="HammerWeight";

  for(int i=1; i< numWeights; i=i+2)

  {

	  weightsToTest[i]="HammerWeight"+TString::Itoa(i/2,10)+"_p1";

	  weightsToTest[i+1]="HammerWeight"+TString::Itoa(i/2,10)+"_m1";

  }


  //Set up branches

  tham->SetBranchAddress("eventNumber",&eventNumberHam);

  tham->SetBranchAddress("runNumber",&runNumberHam);

  tham->BuildIndex("runNumber","eventNumber");



  tin->SetBranchAddress("Bc_MM",&Mvis); //Jpsi+mu visible mass

  tin->SetBranchAddress("eventNumber",&eventNumber);

  tin->SetBranchAddress("runNumber",&runNumber);

  for(int i=0; i<numWeights; i++) //set up branch weights in an easy-to-loop format

  {

    //to cross-reference in tham do:

      tham->SetBranchAddress(weightsToTest[i],&weights[i]); //NOTE: probably exist in tham 

      sumW[i]=0.;

      sumWpass[i]=0.;

      sumW2[i]=0.;

  }


  int n = tin->GetEntries();

  for(int i=0; i<n; i++)

  {

    tin->GetEntry(i);

    if(tham->GetEntryWithIndex(runNumber,eventNumber) > 0) 

    {

      for(int j=0; j<numWeights; j++)

      {

        sumW[j]+= 1;//weights[j];
        
	if(Mvis > 5300)

        {

          sumWpass[j]+= 1;//weights[j];

        }

      }

    }

  }



  for(int i=0; i < numWeights; i++)

  {

    cout << weightsToTest[i] << ":    \t"

	 << sumWpass[i] << "/" << sumW[i] << '\t'

	 << "\tMass Cut Eff (%): " << 100*sumWpass[i]/sumW[i] << endl;

  }

    

}

  
