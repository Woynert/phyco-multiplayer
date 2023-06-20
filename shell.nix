{ pkgs ? import <nixpkgs> {} # here we import the nixpkgs package set
}:
pkgs.mkShell {
	name="dev-environment";
	buildInputs = [
		pkgs.git
		pkgs.bear

		pkgs.gcc12
		pkgs.python39
		pkgs.scons
		pkgs.pkgconf
		pkgs.xorg.libX11
		pkgs.xorg.libXcursor
		pkgs.xorg.libXinerama
		pkgs.xorg.libXi
		pkgs.xorg.libXrandr
		pkgs.mesa
		pkgs.alsa-lib
		pkgs.libpulseaudio
		pkgs.libudev-zero
	];
	shellHook = ''
		echo "Welcome to Godot dev env ---"

		GODOT_PATH=/appimages/Godot_misc/Godot_v4.0.3-stable_linux.x86_64/
		export PATH=$PATH:$GODOT_PATH

		# custom prompt
		if [ -e ~/.gitconfig ] && [ -f ~/.git-prompt.sh ]; then
			source ~/.git-prompt.sh
			PS1='\[\033[01;33m\]nix:\w\[\033[01;34m\]$(__git_ps1 " %s")\[\033[33m\]\$\[\033[00m\] '
		fi
	'';
}
