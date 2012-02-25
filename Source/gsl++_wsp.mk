.PHONY: clean All

All:
	@echo ----------Building project:[ Autotest - Debug ]----------
	@cd "Autotest" && "$(MAKE)" -f "Autotest.mk"
clean:
	@echo ----------Cleaning project:[ Autotest - Debug ]----------
	@cd "Autotest" && "$(MAKE)" -f "Autotest.mk" clean
