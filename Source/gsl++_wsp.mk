.PHONY: clean All

All:
	@echo ----------Building project:[ gslpp - Debug ]----------
	@cd "gslpp" && "$(MAKE)" -f "gslpp.mk"
	@echo ----------Building project:[ Autotest - Debug ]----------
	@cd "Autotest" && "$(MAKE)" -f "Autotest.mk"
clean:
	@echo ----------Cleaning project:[ gslpp - Debug ]----------
	@cd "gslpp" && "$(MAKE)" -f "gslpp.mk"  clean
	@echo ----------Cleaning project:[ Autotest - Debug ]----------
	@cd "Autotest" && "$(MAKE)" -f "Autotest.mk" clean
