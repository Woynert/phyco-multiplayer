#/usr/bin/env bash

case $1 in

	"clang-check")
		echo "Checking formatting..."
		exec clang-format --dry-run -Werror -ferror-limit=1 `find ./src -type f -regex '.*\.\(cpp\|hpp\|h\)'`
		;;

	"clang-format")
		echo "Applying formatting..."
		exec clang-format -i `find ./src -type f -regex '.*\.\(cpp\|hpp\|h\)'`
		;;

	*)
		echo "Not recognized"
		;;
esac

exit 1
