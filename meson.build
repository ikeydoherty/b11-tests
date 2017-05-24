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

compiler = meson.get_compiler('cpp')

kde_wanted_components = [
    'WindowSystem',
]

dep_kf5 = []

foreach kde_component: kde_wanted_components
    dep_tmp_lib = compiler.find_library('KF5' + kde_component)
    dep_tmp_kf5 = declare_dependency(
        dependencies: [
            dep_tmp_lib,
        ],
        include_directories: [
            include_directories('/usr/include/KF5/K' + kde_component),
        ],
    )
    dep_kf5 += dep_tmp_kf5
endforeach

panel_mocs = qt5.preprocess(
    moc_headers: [
        'src/panel.h',
        'src/taskbutton.h',
    ],
)

executable(
    'b11-panel',
    [
        'src/b11-panel.cpp',
        'src/panel.cpp',
        'src/taskbutton.cpp',
        panel_mocs,
    ],
    dependencies: [
        dep_qtwidgets,
        dep_kf5,
    ],
)
