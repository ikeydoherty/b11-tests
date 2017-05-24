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

qt5 = import('qt5')
qt_min_version = '5.6.2'
dep_qtwidgets = dependency('Qt5Widgets', version: qt_min_version)


panel_mocs = qt5.preprocess(
    moc_headers: [
        'src/panel.h',
    ],
)
executable(
    'b11-panel',
    [
        'src/b11-panel.cpp',
        'src/panel.cpp',
        panel_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
    ],
)
