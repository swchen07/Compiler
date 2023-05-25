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

void IRGenerator::CreateVar(VarType type, std::string name, llvm::Value* value){
    this->varList_.push_back(new IRVarAttr(type, name, value));
    if (this->curBasicBlock_) this->curBasicBlock_->varCnt_ += 1; 
}

void IRGenerator::DiscardVar() {
    if (this->curBasicBlock_)
        for (int i = 0; i < this->curBasicBlock_->varCnt_; i++) {
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

void IRGenerator::SetPreBrSignal() {
    this->bbCreatePreBrSignal_ = true; 
}

bool IRGenerator::ClearPreBrSignal() {
    bool bbCreatePreBrSignal = this->bbCreatePreBrSignal_; 
    this->bbCreatePreBrSignal_ = false;
    return bbCreatePreBrSignal;
}

bool IRGenerator::GetPreBrSignal() {
    return this->bbCreatePreBrSignal_; 
}

BlockAST* IRGenerator::GetBasicBlock() {
    return this->curBasicBlock_; 
}

void IRGenerator::SetBasicBlock(BlockAST* newBasicBlock){
    this->curBasicBlock_ = newBasicBlock; 
}

llvm::Value* IRGenerator::FindVar(std::string name){
	if(this->varList_.size() == 0){
		return NULL;
	}
	for(auto symbol = this->varList_.end() - 1; symbol >= this->varList_.begin(); symbol--){
		if((*symbol)->name_ == name){
			return (*symbol)->value_;
		}
	}
	return NULL;
}



void IRGenerator::CreateFunc(llvm::FunctionType* type, std::string name, llvm::Function* func){
    this->funcList_.push_back(new IRFuncAttr(type, name, func));
}

void IRGenerator::DiscardFunc(int cnt) {
    for (int i = 0; i < cnt; i++) {
        auto func = this->funcList_[this->funcList_.size()-1];
		this->funcList_.pop_back();
        delete func; 
    }
}

llvm::Function* IRGenerator::FindFunction(std::string Name) {
	if (this->funcList_.size() == 0) return NULL;
    for (auto iter = this->funcList_[this->funcList_.size()-1]; iter >= this->funcList_[0]; iter--) {
        if (iter->getName() == Name){
            return iter->getFunc();
        }
    }
	return NULL;
}