
# How to install gtk on Mac
Not that complicated, if you have homebrew installed it is super easy just execute
these commands. THe first one install gtk and the second install the required
libraries to gtk work.

```bash
brew install gtk4
brew install pkg-config
```

# How to enable GTK library documentation on Vscode
Add this to your c_cpp_properties.json. This file can be acessed by
Ctrl+Shift+P and searching for Edit Configuration.

```json
"includePath": [
                "${workspaceFolder}/**",
                "/opt/homebrew/include/gtk-4.0",
                "/opt/homebrew/include/glib-2.0",
                "/opt/homebrew/lib/glib-2.0/include",
                "/opt/homebrew/include/pango-1.0",
                "/opt/homebrew/include/cairo",
                "/opt/homebrew/include/gdk-pixbuf-2.0",
                "/opt/homebrew/include/graphene-1.0",
                "/opt/homebrew/lib/graphene-1.0/include",
                "/opt/homebrew/include/harfbuzz"
            ],
```
