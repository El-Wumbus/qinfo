project('qinfo', 'c')

cc = meson.get_compiler('c')
dmath = cc.find_library('m', required: false)


executable(
    'qinfo',
    'src/config.c',
    'src/cpu.c',
    'src/qinfo.c',
    'src/statx.c',
    'src/linux.c',
    'src/win32.c',
    'library/ini.c',
    dependencies: dmath
)