{
    "targets": [
        {
            "target_name": "display-js",
            "sources": [
                "native/binding.c"
            ],
            "conditions": [
                [
                    'OS=="mac"', {
                        "sources": [
                            "native/mac/Display.m",
                        ],
                        "xcode_settings": {
                            "OTHER_LDFLAGS": ["-framework CoreGraphics"]
                        }
                    }
                ]
            ]
        }
    ]
}