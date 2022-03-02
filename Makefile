build_folder = build
CC = clang
headers = include

$(build_folder)/test.o: test/test.cpp test/catch.hpp
	$(CC) $< -c -o $@

$(build_folder)/geometry.o: $(headers)/geometry.cpp
	$(CC) $< -c -o $@

$(build_folder)/canvas.o: $(headers)/canvas.cpp
	$(CC) $< -c -o $@

tests: $(build_folder)/test.o $(build_folder)/geometry.o $(build_folder)/canvas.o
	$(CC) $^ -o $(build_folder)/test.exe
	./$(build_folder)/test.exe -d yes
ray:
	$(CC) src/raytracer.cpp -o raytracer.exe