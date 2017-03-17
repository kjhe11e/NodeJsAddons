{
    "targets": [
        {
            "target_name": "pow",
            "sources": [ "pow.cpp" ],
            "include_dirs": [
                "<!(node -e \"require('nan') \")"
            ]
        }
    ]
}
