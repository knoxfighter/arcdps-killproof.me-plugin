# arcdps killproof.me plugin
A Plugin for arcdps, that is loading killproof.me info and displaying it ingame.

## Contact
For any errors, feature requests and questions, simply open a new issue here.  
You can also join the [Elite Insights discord](https://discord.gg/dCDEPXx) and write in the channel #killproof-me-plugin.  

## Installation
Requires [ArcDPS](https://www.deltaconnected.com/arcdps/).

Download the latest version from the [releases page](https://github.com/knoxfighter/arcdps-killproof.me-plugin/releases/latest).  
Then put the .dll file into the same folder as arcdps or in `<Guild Wars 2>/bin64`.  
To disable, just remove the .dll file.

To allow tracking of players outside your current instance, install the [unofficial-extras addon](https://github.com/Krappa322/arcdps_unofficial_extras_releases/releases/latest).

Alternatively, install it with the [Guild Wars 2 Addon manager](https://github.com/fmmmlee/GW2-Addon-Manager/), like multiple other plugins.

## Troubleshooting
If the DLL is not loaded (options do not show up), make sure, that you have installed the latest C++ 2015-2022 Redistributable.
You can download the latest Redistributable from [Microsofts download page](https://docs.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist).
Please use the version "Visual Studio 2015, 2017, 2019 and 2022".  
If you have problems, that your settings are reset on each startup, delete the file `<GW2>/addons/arcdps/arcdps_killproof.me.json`. This will reset all your settings.

## Usage
Don't be a dick and give people a chance!

This plugin will load the killproof.me profiles, from everybody in your group, when they are on the same map, than you are. Those information, can be accessed in the killproof.me windows. No information is shown, when the individual has no killproof.me account or it is on private.

Two way to open the window:  
- Open the arcdps options panel (Alt+Shift+T by default) and enable the "Killproofs" checkbox.
- Use the hotkey Alt+Shift+K. This can be adjusted in the Settings menu (opened also in the arcdps options panel, in  "Killproof.me").

To close the window, just press the X on the top right, press Escape or use the hotkey Alt+Shift+K again.  
To change what is shown in the table, press rightclick on the header. The table can be sorted by every column, just click on the header.  
The killproof.me website will be opened, when you click on the accountname or on the username.

![Ingame screenshot](screenshot.png)

## Translations
The plugin is translated to English, French, German and Spanish. Translations, except english are only roughly, so please report any problems with them.
There is no chinese translation yet, if you want to add one, go ahead.

## Development

This plugin was developed with visual studio 2022 and vcpkg. It has only one dependency, that has to be installed in vcpkg.

Setup vcpk and make it available within visual studio:
```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
```

Then download this project and open it with Visual Studio. Everything should be set up and you should be able to compile it.  
The default output directory is `C:\Program Files\Guild Wars 2\bin64\`, you can change that in `Properties -> Configuration Properties -> General -> Output Directory`.
Also, running the Local Windows Debugger, will start `C:\Program Files\Guild Wars 2\Gw2-64.exe` and attaches the debugger to it. Make sure to NOT use your normal account, cause you could get banned for it!

## LICENSE

This project is licensed with the MIT License.

### Dear ImGui
[Dear ImGui](https://github.com/ocornut/imgui) is also licensed with the MIT License and included as git submodule to this project. Used is a fork of it that adds a visual studio project.

### json
[json](https://github.com/nlohmann/json) is a json library created by nlohmann and licensed with the MIT License. It is included with vcpkg.

### cpr
[cpr](https://github.com/whoshuu/cpr) is a http library, that is licensed with the MIT License. It is included with vcpkg and itself has dependencies.

### magic_enum
[magic_enum](https://github.com/Neargye/magic_enum) is licensed with the MIT License. It is included with vcpkg.

### arcdps-extension
[arcdps-extension](https://github.com/knoxfighter/arcdps-extension/) is licensed with the MIT License. Also developed by myself.

### arcdps-unofficial-extras
[arcdps_unofficial_extras_releases](https://github.com/Krappa322/arcdps_unofficial_extras_releases) is a closed source addon that this addon can use. The public API included is licensed with the MIT License. Also partially developed by myself.
