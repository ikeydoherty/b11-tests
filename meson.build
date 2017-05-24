project(
    'b11-tests',
    ['cpp'],
    version: '0',
    license: [
        'LGPL-2.1',
    ],
    default_options: [
        'cpp_std=c++14',
    ],
)

qt_min_version = '5.6.2'
dep_qtwidgets = dependency('Qt5Widgets', version: qt_min_version)

executable(
    'b11-panel',
    [
        'src/b11-panel.cpp',
        'src/panel.cpp',
    ],
    dependencies: [
        dep_qtwidgets,
    ],
)
