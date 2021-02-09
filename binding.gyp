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
                ]
            ]
        }
    ]
}