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
                ]
            ]
        }
    ]
}