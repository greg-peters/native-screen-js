{
    "targets": [
        {
            "target_name": "displayJS",
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