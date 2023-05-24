#include "AST.hpp"
#include "IRGenerator.hpp"

void IRGenerator::GenerateCode(BaseAST* root) {
    root->IRGen(*this);
	this->Module->print(llvm::outs(), NULL);
}

void IRGenerator::GenObjectCode(std::string outputfile) {
	auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    auto Features = "";
    auto CPU = "generic";
    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
    Module->setDataLayout(TargetMachine->createDataLayout());
    Module->setTargetTriple(TargetTriple);

    std::error_code EC;
    llvm::raw_fd_ostream Dest(outputfile, EC, llvm::sys::fs::OF_None);

    auto FileType = llvm::CGFT_ObjectFile;
    llvm::legacy::PassManager PM;
    TargetMachine->addPassesToEmitFile(PM, Dest, nullptr, FileType);

    PM.run(*Module);
    Dest.flush();
}

void IRGenerator::CreateVar(TypeID type, std::string name, llvm::Value* value){
    this->varList_.push_back(new IRVarAttr(type, name, value));
}

void IRGenerator::DiscardVar(int cnt) {
    for (int i = 0; i < cnt; i++) {
        auto var = this->varList_[this->varList_.size()-1];
		this->varList_.pop_back();
        delete var; 
    }
}

void IRGenerator::SetCurFunc(llvm::Function* curFunc) {
    this->curFunc_ = curFunc; 
}

llvm::Function* IRGenerator::GetCurFunc() {
    return this->curFunc_; 
}

void IRGenerator::setPreBrSignal() {
    this->bbCreatePreBrSignal_ = true; 
}

bool IRGenerator::clearPreBrSignal() {
    bool bbCreatePreBrSignal = this->bbCreatePreBrSignal_; 
    this->bbCreatePreBrSignal_ = false;
    return bbCreatePreBrSignal;
}

bool IRGenerator::getPreBrSignal() {
    return this->bbCreatePreBrSignal_; 
}