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
Date                   :=21/08/11
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
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -pedantic -Wall $(Preprocessors)
C_CmpOptions           := -g -pedantic -Wall $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch).. $(IncludeSwitch)/usr/local/include $(IncludeSwitch)/usr/include 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)gsl++ $(LibrarySwitch)cppunit 
LibPath                := $(LibraryPathSwitch). 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/permutationtestsuite$(ObjectSuffix) $(IntermediateDirectory)/sorttestsuite$(ObjectSuffix) $(IntermediateDirectory)/vectortestsuite$(ObjectSuffix) $(IntermediateDirectory)/matrixtestsuite$(ObjectSuffix) $(IntermediateDirectory)/combinationtestsuite$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

makeDirStep:
	@test -d ../.. || $(MakeDirCommand) ../..

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/main.cpp"

$(IntermediateDirectory)/permutationtestsuite$(ObjectSuffix): permutationtestsuite.cpp $(IntermediateDirectory)/permutationtestsuite$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/permutationtestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/permutationtestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/permutationtestsuite$(DependSuffix): permutationtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/permutationtestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/permutationtestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/permutationtestsuite.cpp"

$(IntermediateDirectory)/permutationtestsuite$(PreprocessSuffix): permutationtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/permutationtestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/permutationtestsuite.cpp"

$(IntermediateDirectory)/sorttestsuite$(ObjectSuffix): sorttestsuite.cpp $(IntermediateDirectory)/sorttestsuite$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/sorttestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sorttestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sorttestsuite$(DependSuffix): sorttestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sorttestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/sorttestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/sorttestsuite.cpp"

$(IntermediateDirectory)/sorttestsuite$(PreprocessSuffix): sorttestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sorttestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/sorttestsuite.cpp"

$(IntermediateDirectory)/vectortestsuite$(ObjectSuffix): vectortestsuite.cpp $(IntermediateDirectory)/vectortestsuite$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/vectortestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/vectortestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vectortestsuite$(DependSuffix): vectortestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vectortestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/vectortestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/vectortestsuite.cpp"

$(IntermediateDirectory)/vectortestsuite$(PreprocessSuffix): vectortestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vectortestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/vectortestsuite.cpp"

$(IntermediateDirectory)/matrixtestsuite$(ObjectSuffix): matrixtestsuite.cpp $(IntermediateDirectory)/matrixtestsuite$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/matrixtestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/matrixtestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/matrixtestsuite$(DependSuffix): matrixtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/matrixtestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/matrixtestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/matrixtestsuite.cpp"

$(IntermediateDirectory)/matrixtestsuite$(PreprocessSuffix): matrixtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/matrixtestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/matrixtestsuite.cpp"

$(IntermediateDirectory)/combinationtestsuite$(ObjectSuffix): combinationtestsuite.cpp $(IntermediateDirectory)/combinationtestsuite$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/combinationtestsuite.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/combinationtestsuite$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/combinationtestsuite$(DependSuffix): combinationtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/combinationtestsuite$(ObjectSuffix) -MF$(IntermediateDirectory)/combinationtestsuite$(DependSuffix) -MM "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/combinationtestsuite.cpp"

$(IntermediateDirectory)/combinationtestsuite$(PreprocessSuffix): combinationtestsuite.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/combinationtestsuite$(PreprocessSuffix) "/home/kevin/.codelite/Solutions/gsl++/Source/Autotest/combinationtestsuite.cpp"


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
	$(RM) $(OutputFile)

