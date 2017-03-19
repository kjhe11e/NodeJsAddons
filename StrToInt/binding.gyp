{
    "targets": [
        {
            "target_name": "strToInt",
            "sources": [ "strToInt.cpp" ],
            "include_dirs": [
                "<!(node -e \"require('nan') \")"
            ]
        }
    ]
}
