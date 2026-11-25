#define NOB_IMPLEMENTATION
#include "nob-lib/nob.h"

#define gab_add_test(cmd, test_name) \
	do { \
		nob_cmd_append((cmd), "test/" #test_name "_test.c"); \
	} while (0) \

int main(int argc, char** argv) {
	NOB_GO_REBUILD_URSELF(argc, argv);

	Nob_Cmd test_build_cmd = {0};

	nob_cmd_append(&test_build_cmd, "clang");

	gab_add_test(&test_build_cmd, vector);

	nob_cmd_append(
		&test_build_cmd,
		"-w",
		"-std=c17",
		"-lcriterion",
		"-fsanitize=address",
		"-o",
		"tests"
	);

	if (!nob_cmd_run(&test_build_cmd))
		return 1;

	Nob_Cmd test_run_cmd = {0};

	nob_cmd_append(
		&test_run_cmd,
		"./tests",
	);

	if (nob_cmd_run(&test_run_cmd))
		return 0;

	Nob_Cmd rerun_build = {0};

	nob_cmd_append(&rerun_build, "clang");

	gab_add_test(&rerun_build, vector);

	nob_cmd_append(
		&rerun_build,
		"-Wall",
		"-Wextra",
		"-std=c17",
		"-lcriterion",
		"-o",
		"tests"
	);

	nob_cmd_run(&rerun_build);

	return 0;
}
