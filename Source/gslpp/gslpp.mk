##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=gslpp
ConfigurationName      :=Debug
IntermediateDirectory  :=../..
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/kevin/.codelite/Solutions/gsl++/Source"
ProjectPath            := "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Kevin Channon
Date                   :=11/09/11
CodeLitePath           :="/home/kevin/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/Targets/Debug/libgsl++.so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/gslpp.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -pedantic -Wall  -DGSLPP_INLINE -std=gnu++0x $(Preprocessors)
C_CmpOptions           := -g -pedantic -Wall $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)/usr/local/include $(IncludeSwitch)/usr/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gsl $(LibrarySwitch)gslcblas $(LibrarySwitch)z 
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/Matrix_matrix$(ObjectSuffix) $(IntermediateDirectory)/Permutation_permutation$(ObjectSuffix) $(IntermediateDirectory)/Permutation_permute$(ObjectSuffix) $(IntermediateDirectory)/Sort_sort$(ObjectSuffix) $(IntermediateDirectory)/Combination_combination$(ObjectSuffix) $(IntermediateDirectory)/blas_blas1$(ObjectSuffix) $(IntermediateDirectory)/Complex_complex$(ObjectSuffix) $(IntermediateDirectory)/Polynomial_polynomial$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "/home/kevin/.codelite/Solutions/gsl++/Source/.build-debug"
	@echo rebuilt > "/home/kevin/.codelite/Solutions/gsl++/Source/.build-debug/gslpp"

$(IntermediateDirectory)/.d:
	@test -d ../.. || $(MakeDirCommand) ../..

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Matrix_matrix$(ObjectSuffix): Matrix/matrix.cpp $(IntermediateDirectory)/Matrix_matrix$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Matrix/matrix.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Matrix_matrix$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Matrix_matrix$(DependSuffix): Matrix/matrix.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Matrix_matrix$(ObjectSuffix) -MF$(IntermediateDirectory)/Matrix_matrix$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Matrix/matrix.cpp"

$(IntermediateDirectory)/Matrix_matrix$(PreprocessSuffix): Matrix/matrix.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Matrix_matrix$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Matrix/matrix.cpp"

$(IntermediateDirectory)/Permutation_permutation$(ObjectSuffix): Permutation/permutation.cpp $(IntermediateDirectory)/Permutation_permutation$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Permutation/permutation.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Permutation_permutation$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Permutation_permutation$(DependSuffix): Permutation/permutation.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Permutation_permutation$(ObjectSuffix) -MF$(IntermediateDirectory)/Permutation_permutation$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Permutation/permutation.cpp"

$(IntermediateDirectory)/Permutation_permutation$(PreprocessSuffix): Permutation/permutation.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Permutation_permutation$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Permutation/permutation.cpp"

$(IntermediateDirectory)/Permutation_permute$(ObjectSuffix): Permutation/permute.cpp $(IntermediateDirectory)/Permutation_permute$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Permutation/permute.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Permutation_permute$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Permutation_permute$(DependSuffix): Permutation/permute.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Permutation_permute$(ObjectSuffix) -MF$(IntermediateDirectory)/Permutation_permute$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Permutation/permute.cpp"

$(IntermediateDirectory)/Permutation_permute$(PreprocessSuffix): Permutation/permute.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Permutation_permute$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Permutation/permute.cpp"

$(IntermediateDirectory)/Sort_sort$(ObjectSuffix): Sort/sort.cpp $(IntermediateDirectory)/Sort_sort$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Sort/sort.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Sort_sort$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sort_sort$(DependSuffix): Sort/sort.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Sort_sort$(ObjectSuffix) -MF$(IntermediateDirectory)/Sort_sort$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Sort/sort.cpp"

$(IntermediateDirectory)/Sort_sort$(PreprocessSuffix): Sort/sort.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Sort_sort$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Sort/sort.cpp"

$(IntermediateDirectory)/Combination_combination$(ObjectSuffix): Combination/combination.cpp $(IntermediateDirectory)/Combination_combination$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Combination/combination.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Combination_combination$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Combination_combination$(DependSuffix): Combination/combination.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Combination_combination$(ObjectSuffix) -MF$(IntermediateDirectory)/Combination_combination$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Combination/combination.cpp"

$(IntermediateDirectory)/Combination_combination$(PreprocessSuffix): Combination/combination.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Combination_combination$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Combination/combination.cpp"

$(IntermediateDirectory)/blas_blas1$(ObjectSuffix): blas/blas1.cpp $(IntermediateDirectory)/blas_blas1$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/blas/blas1.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/blas_blas1$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/blas_blas1$(DependSuffix): blas/blas1.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/blas_blas1$(ObjectSuffix) -MF$(IntermediateDirectory)/blas_blas1$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/blas/blas1.cpp"

$(IntermediateDirectory)/blas_blas1$(PreprocessSuffix): blas/blas1.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/blas_blas1$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/blas/blas1.cpp"

$(IntermediateDirectory)/Complex_complex$(ObjectSuffix): Complex/complex.cpp $(IntermediateDirectory)/Complex_complex$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Complex/complex.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Complex_complex$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Complex_complex$(DependSuffix): Complex/complex.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Complex_complex$(ObjectSuffix) -MF$(IntermediateDirectory)/Complex_complex$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Complex/complex.cpp"

$(IntermediateDirectory)/Complex_complex$(PreprocessSuffix): Complex/complex.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Complex_complex$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Complex/complex.cpp"

$(IntermediateDirectory)/Polynomial_polynomial$(ObjectSuffix): Polynomial/polynomial.cpp $(IntermediateDirectory)/Polynomial_polynomial$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Polynomial/polynomial.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Polynomial_polynomial$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Polynomial_polynomial$(DependSuffix): Polynomial/polynomial.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Polynomial_polynomial$(ObjectSuffix) -MF$(IntermediateDirectory)/Polynomial_polynomial$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Polynomial/polynomial.cpp"

$(IntermediateDirectory)/Polynomial_polynomial$(PreprocessSuffix): Polynomial/polynomial.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Polynomial_polynomial$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/gslpp/Polynomial/polynomial.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Matrix_matrix$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Matrix_matrix$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Matrix_matrix$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Permutation_permutation$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Permutation_permutation$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Permutation_permutation$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Permutation_permute$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Permutation_permute$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Permutation_permute$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Sort_sort$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Sort_sort$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Sort_sort$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Combination_combination$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Combination_combination$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Combination_combination$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/blas_blas1$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/blas_blas1$(DependSuffix)
	$(RM) $(IntermediateDirectory)/blas_blas1$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Complex_complex$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Complex_complex$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Complex_complex$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Polynomial_polynomial$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Polynomial_polynomial$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Polynomial_polynomial$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/kevin/.codelite/Solutions/gsl++/Source/.build-debug/gslpp"


