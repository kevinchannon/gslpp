.PHONY: clean All

All:
	@echo ----------Building project:[ gslpp - Debug ]----------
	@cd "gslpp" && "$(MAKE)" -f "gslpp.mk"
clean:
	@echo ----------Cleaning project:[ gslpp - Debug ]----------
	@cd "gslpp" && "$(MAKE)" -f "gslpp.mk" clean
