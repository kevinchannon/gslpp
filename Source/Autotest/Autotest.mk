##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Autotest
ConfigurationName      :=Debug
IntermediateDirectory  :=../..
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/kevin/.codelite/Solutions/gsl++/Source"
ProjectPath            := "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Kevin Channon
Date                   :=18/09/11
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
OutputFile             :=$(IntermediateDirectory)/Targets/Debug/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/Autotest.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -pedantic -Wall  -DGSLPP_INLINE $(Preprocessors)
C_CmpOptions           := -g -pedantic -Wall $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch).. $(IncludeSwitch)/usr/local/include $(IncludeSwitch)/usr/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gsl++ $(LibrarySwitch)cppunit 
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/permutationtestsuite$(ObjectSuffix) $(IntermediateDirectory)/sorttestsuite$(ObjectSuffix) $(IntermediateDirectory)/vectortestsuite$(ObjectSuffix) $(IntermediateDirectory)/matrixtestsuite$(ObjectSuffix) $(IntermediateDirectory)/combinationtestsuite$(ObjectSuffix) $(IntermediateDirectory)/complextestsuite$(ObjectSuffix) $(IntermediateDirectory)/mathfunctionstestsuite$(ObjectSuffix) $(IntermediateDirectory)/blocktestsuite$(ObjectSuffix) $(IntermediateDirectory)/polynomialtestsuite$(ObjectSuffix) \
	

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d ../.build-debug/gslpp $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

../.build-debug/gslpp:
	@echo stam > "../.build-debug/gslpp"




$(IntermediateDirectory)/.d:
	@test -d ../.. || $(MakeDirCommand) ../..

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/main.cpp"

$(IntermediateDirectory)/permutationtestsuite$(ObjectSuffix): permutationtestsuite.cpp $(IntermediateDirectory)/permutationtestsuite$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/permutationtestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/permutationtestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/permutationtestsuite$(DependSuffix): permutationtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/permutationtestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/permutationtestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/permutationtestsuite.cpp"

$(IntermediateDirectory)/permutationtestsuite$(PreprocessSuffix): permutationtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/permutationtestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/permutationtestsuite.cpp"

$(IntermediateDirectory)/sorttestsuite$(ObjectSuffix): sorttestsuite.cpp $(IntermediateDirectory)/sorttestsuite$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/sorttestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sorttestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sorttestsuite$(DependSuffix): sorttestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sorttestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/sorttestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/sorttestsuite.cpp"

$(IntermediateDirectory)/sorttestsuite$(PreprocessSuffix): sorttestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sorttestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/sorttestsuite.cpp"

$(IntermediateDirectory)/vectortestsuite$(ObjectSuffix): vectortestsuite.cpp $(IntermediateDirectory)/vectortestsuite$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/vectortestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/vectortestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vectortestsuite$(DependSuffix): vectortestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vectortestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/vectortestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/vectortestsuite.cpp"

$(IntermediateDirectory)/vectortestsuite$(PreprocessSuffix): vectortestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vectortestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/vectortestsuite.cpp"

$(IntermediateDirectory)/matrixtestsuite$(ObjectSuffix): matrixtestsuite.cpp $(IntermediateDirectory)/matrixtestsuite$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/matrixtestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/matrixtestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/matrixtestsuite$(DependSuffix): matrixtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/matrixtestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/matrixtestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/matrixtestsuite.cpp"

$(IntermediateDirectory)/matrixtestsuite$(PreprocessSuffix): matrixtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/matrixtestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/matrixtestsuite.cpp"

$(IntermediateDirectory)/combinationtestsuite$(ObjectSuffix): combinationtestsuite.cpp $(IntermediateDirectory)/combinationtestsuite$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/combinationtestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/combinationtestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/combinationtestsuite$(DependSuffix): combinationtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/combinationtestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/combinationtestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/combinationtestsuite.cpp"

$(IntermediateDirectory)/combinationtestsuite$(PreprocessSuffix): combinationtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/combinationtestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/combinationtestsuite.cpp"

$(IntermediateDirectory)/complextestsuite$(ObjectSuffix): complextestsuite.cpp $(IntermediateDirectory)/complextestsuite$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/complextestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/complextestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/complextestsuite$(DependSuffix): complextestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/complextestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/complextestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/complextestsuite.cpp"

$(IntermediateDirectory)/complextestsuite$(PreprocessSuffix): complextestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/complextestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/complextestsuite.cpp"

$(IntermediateDirectory)/mathfunctionstestsuite$(ObjectSuffix): mathfunctionstestsuite.cpp $(IntermediateDirectory)/mathfunctionstestsuite$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/mathfunctionstestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/mathfunctionstestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mathfunctionstestsuite$(DependSuffix): mathfunctionstestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mathfunctionstestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/mathfunctionstestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/mathfunctionstestsuite.cpp"

$(IntermediateDirectory)/mathfunctionstestsuite$(PreprocessSuffix): mathfunctionstestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mathfunctionstestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/mathfunctionstestsuite.cpp"

$(IntermediateDirectory)/blocktestsuite$(ObjectSuffix): blocktestsuite.cpp $(IntermediateDirectory)/blocktestsuite$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/blocktestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/blocktestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/blocktestsuite$(DependSuffix): blocktestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/blocktestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/blocktestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/blocktestsuite.cpp"

$(IntermediateDirectory)/blocktestsuite$(PreprocessSuffix): blocktestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/blocktestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/blocktestsuite.cpp"

$(IntermediateDirectory)/polynomialtestsuite$(ObjectSuffix): polynomialtestsuite.cpp $(IntermediateDirectory)/polynomialtestsuite$(DependSuffix)
	$(CompilerName) $(IncludePCH) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/polynomialtestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/polynomialtestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/polynomialtestsuite$(DependSuffix): polynomialtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/polynomialtestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/polynomialtestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/polynomialtestsuite.cpp"

$(IntermediateDirectory)/polynomialtestsuite$(PreprocessSuffix): polynomialtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/polynomialtestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/polynomialtestsuite.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/permutationtestsuite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/permutationtestsuite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/permutationtestsuite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sorttestsuite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sorttestsuite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sorttestsuite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/vectortestsuite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/vectortestsuite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/vectortestsuite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/matrixtestsuite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/matrixtestsuite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/matrixtestsuite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/combinationtestsuite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/combinationtestsuite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/combinationtestsuite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/complextestsuite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/complextestsuite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/complextestsuite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/mathfunctionstestsuite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mathfunctionstestsuite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mathfunctionstestsuite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/blocktestsuite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/blocktestsuite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/blocktestsuite$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/polynomialtestsuite$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/polynomialtestsuite$(DependSuffix)
	$(RM) $(IntermediateDirectory)/polynomialtestsuite$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "/home/kevin/.codelite/Solutions/gsl++/Source/.build-debug/Autotest"


