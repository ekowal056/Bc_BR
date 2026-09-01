////////////////////////////////////
///
///
///
////////////////////////////////////////

{

/// Load in Files

TFile *JpsiMuRoot = new TFile("Bc2JpsiMu_step1_sim18.root", "Read");
TTree *JpsiMu=dynamic_cast<TTree*>(JpsiMuRoot->Get("DecayTree"));

TFile *Psi2SMuRoot = new TFile("BKG_Step1/Bc2Psi2SMu_ebert_step1.root", "Read");
TTree *Psi2SMu=dynamic_cast<TTree*>(Psi2SMuRoot->Get("DecayTree"));

//TFile *Chic1MuRoot = new TFile("BKG_Step1/Bc2Chic1Mu_step1.root", "Read");
//TTree *Chic1Mu=dynamic_cast<TTree*>(Chic1MuRoot->Get("DecayTree"));

//TFile *Chic2MuRoot = new TFile("BKG_Step1/Bc2Chic2Mu_step1.root", "Read");
//TTree *Chic2Mu=dynamic_cast<TTree*>(Chic2MuRoot->Get("DecayTree"));


/// Calculate the number of events each should have

int JpsiMuEvents = JpsiMu->GetEntries();
int JpsiMuScale = 8520;

//int numJpsiD  = JpsiMuEvents*55/JpsiMuScale;
//int numJpsiDstst  = JpsiMuEvents*17/JpsiMuScale;
//int numJpsiDK  = JpsiMuEvents*5/JpsiMuScale;
int numPsi2SMu  = JpsiMuEvents*260/JpsiMuScale;
//int numPsi2STau  = JpsiMuEvents*2/JpsiMuScale;
//int numChic1Mu  = JpsiMuEvents*277/JpsiMuScale;
//int numChic2Mu  = JpsiMuEvents*277/JpsiMuScale;
//int nummisID  = JpsiMuEvents*2074/JpsiMuScale;
//int numJpsiTau  = JpsiMuEvents*426/JpsiMuScale;
//int numBud2JpsiX  = JpsiMuEvents*87/JpsiMuScale;
//int numBs2JpsiX  = JpsiMuEvents*10/JpsiMuScale;



////////////////////////////
std::cout<< "Everything is set Up!" << std::endl;

TFile *outFile = TFile::Open("Bc2JpsiMu_fake_data.root","RECREATE");
TTree *outTree = JpsiMu->CloneTree(0);
outTree->CopyEntries(JpsiMu);

std::cout<< "Made the Out Tree!" << std::endl;

std::vector<int> indices(Psi2SMu->GetEntries());
std::iota(indices.begin(), indices.end(), 0);
std::shuffle(indices.begin(), indices.end(), std::mt19937{std::random_device{}()});

Long64_t n = std::min<Long64_t>(numPsi2SMu, indices.size());

std::cout<< "Starting to add " << n  << " Psi2S Mu events!" << std::endl;

TEntryList *entryList = new TEntryList("psi2smu_random_entries","Randomly selected Psi2SMu entries");

double Bc_M;
Psi2SMu->SetBranchAddress("Bc_M", &Bc_M);

for (Long64_t i = 0; i < n; ++i) {
    //Psi2SMu->GetEntry(indices[i]);
    entryList->Enter(indices[i]);
    std::cout<< i<< "/" << n << " Event #"<< indices[i]<< std::endl;//"  Bc Mass: " << Bc_M << std::endl;
}

Psi2SMu->SetEntryList(entryList);
outTree->CopyEntries(Psi2SMu);

Psi2SMu->SetEntryList(nullptr);


std::cout<< "Should have " << JpsiMuEvents+n << " Events" << std::endl;
std::cout<< "Has " << outTree->GetEntries() << " Events" << std::endl;

outFile->Close();

delete entryList;











}
