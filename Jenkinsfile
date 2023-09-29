pipeline {
    agent any

    environment {
        CLANG_TIDY_VERSION = "15.0.2"
        VERBOSE = "1"
    }

    matrix {
        axes {
            axis {
                name 'OS'
                values 'ubuntu-20.04', 'windows-2019'
            }
            axis {
                name 'COMPILER'
                values 'llvm-15.0.2', 'gcc-11'
            }
            axis {
                name 'BUILD_TYPE'
                values 'Release', 'Debug'
            }
            axis {
                name 'PACKAGING_MAINTAINER_MODE'
                values 'ON', 'OFF'
            }
            axis {
                name 'BUILD_SHARED'
                values 'OFF'
            }
        }
        exclude {
            combination(os: 'windows-2019', COMPILER: 'gcc-11')
            combination(os: 'ubuntu-20.04', PACKAGING_MAINTAINER_MODE: 'ON')
        }
        include {
            combination(COMPILER: 'gcc-11', gcov_executable: 'gcov', enable_ipo: 'On')
            combination(COMPILER: 'llvm-15.0.2', enable_ipo: 'Off', gcov_executable: "llvm-cov gcov")
            combination(BUILD_TYPE: 'Release', PACKAGING_MAINTAINER_MODE: 'OFF', package_generator: 'TBZ2')
            combination(os: 'ubuntu-20.04', COMPILER: 'gcc-11', BUILD_TYPE: 'Debug', gcov_executable: 'gcov', PACKAGING_MAINTAINER_MODE: 'On', enable_ipo: 'Off', generator: 'Unix Makefiles')
        }
    }

    stages {
        stage('Test') {
            steps {
                script {
                    if (env.COMPILER.contains('llvm') && !env.COMPILER.contains(env.CLANG_TIDY_VERSION)) {
                        error "There is a mismatch between configured llvm compiler and clang-tidy version chosen"
                    }
                }
                checkout scm

                script {
                    if (env.OS== 'ubuntu-20.04') {
                        sh "wget https://github.com/aminya/setup-cpp/releases/download/v0.35.6/setup-cpp-x64-linux"
                        sh "chmod +x ./setup-cpp-x64-linux"
                        sh "sudo ./setup-cpp-x64-linux --compiler llvm --cmake true --ninja true --ccache true --vcpkg true"
                        sh "source ~/.cpprc"
                    } else if (env.OS == 'windows-2019') {
                        powershell "curl -LJO https://github.com/aminya/setup-cpp/releases/download/v0.35.6/setup-cpp-x64-windows.exe"
                        powershell "./setup-cpp-x64-windows --compiler llvm --cmake true --ninja true --ccache true --vcpkg true"
                        powershell "RefreshEnv.cmd"
                    }
                }
                script {
                    // Configure CMake
                    sh "cmake -S . -B ./build -G \"${env.MATRIX_GENERATOR}\" -D${env.PROJECT_NAME}_ENABLE_IPO=${env.MATRIX_ENABLE_IPO} -DCMAKE_BUILD_TYPE:STRING=${env.MATRIX_BUILD_TYPE} -D${env.PROJECT_NAME}_PACKAGING_MAINTAINER_MODE:BOOL=${env.MATRIX_PACKAGING_MAINTAINER_MODE} -D${env.PROJECT_NAME}_ENABLE_COVERAGE:BOOL=${env.MATRIX_BUILD_TYPE == 'Debug'} -DGIT_SHA:STRING=${env.GITHUB_SHA}"
                }

                script {
                    // Build
                    sh "cmake --build ./build --config ${env.MATRIX_BUILD_TYPE}"
                }
            }
        }
    }
}