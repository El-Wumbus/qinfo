project('qinfo', 'c')

cc = meson.get_compiler('c')
dmath = cc.find_library('m', required: true)

executable(
    'qinfo',
    'src/config.c',
    'src/cpu.c',
    'src/qinfo.c',
    'src/statx.c',
    'src/unix.c',
    'library/ini.c',
    dependencies: dmath
)