{
    "targets": [
        {
            "target_name": "screenJS",
            "sources": [
                "native/binding.c"
            ],
            "conditions": [
                [
                    'OS=="mac"', {
                        "sources": [
                            "native/mac/Screen.m",
                        ],
                        "xcode_settings": {
                            "OTHER_LDFLAGS": ["-framework CoreGraphics"]
                        }
                    }                    
                ],
                [
                    'OS=="win"', {
                        "sources": [
                            "native/win/Screen.c"
                        ],
                        "msvs_settings": {
                            "VCLinkerTool": {
                                # Don't print a linker warning when no imports from either .exe are used.
                                "AdditionalOptions": ["/ignore:4199"],
                            }
                        }
                    }
                ],
                [
                    'OS=="linux"', {
                        "sources": [
                            "native/linux/Screen.c"
                        ],
                        "variables": {
                            "pkg-config": "pkg-config"
                        },
                        "direct_dependent_settings": {
                            "cflags": [
                                "<!@(<(pkg-config) --cflags x11)",
                            ],
                        },
                        "link_settings": {
                            "ldflags": [
                                "<!@(<(pkg-config) --libs-only-other --libs-only-L x11)",
                            ],
                            "libraries": [
                                "<!@(<(pkg-config) --libs-only-l x11)",
                            ]
                        }
                    }
                ]
            ]
        }
    ]
}