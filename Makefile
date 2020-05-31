.PHONY: run test clean-coverage

clean-coverage:
	rm -r .coverage 2>/dev/null || true
	find CMakeFiles -name "*.gcda" -delete

run:
	@ninja main
	@./bin/main

test: clean-coverage
	@ninja tests
	@./bin/tests

