pipeline {
    agent any

    environment {
        CLANG_TIDY_VERSION = "15.0.2"
        VERBOSE = "1"
    }

    stages {
        stage('Test') {
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
                stages {
                    stage('Build and Test') {
                        when {
                            expression {
                                // Exclude logic
                                def exclude = (
                                    (env.OS == 'windows-2019' && env.COMPILER == 'gcc-11') ||
                                    (env.OS == 'ubuntu-20.04' && env.PACKAGING_MAINTAINER_MODE == 'ON')
                                )
                                // Include logic (if needed)
                                def include = true  // Adjust this logic to your needs
                                return !exclude && include
                            }
                        }
                        steps {
                            script {
                                if (env.COMPILER.contains('llvm') && !env.COMPILER.contains(env.CLANG_TIDY_VERSION)) {
                                    error "There is a mismatch between configured llvm compiler and clang-tidy version chosen"
                                }
                            }
                            checkout scm
                            script {
                                if (env.OS == 'ubuntu-20.04') {
                                    sh 'wget "https://github.com/aminya/setup-cpp/releases/download/v0.35.6/setup-cpp-x64-linux"'
                                    sh "chmod +x ./setup-cpp-x64-linux"
                                    sh "./setup-cpp-x64-linux --compiler llvm --cmake true --ninja true --ccache true --vcpkg true"
                                    sh "source ~/.cpprc"
                                } else if (env.OS == 'windows-2019') {
                                    powershell 'curl -LJO "https://github.com/aminya/setup-cpp/releases/download/v0.35.6/setup-cpp-x64-windows.exe"'
                                    powershell "./setup-cpp-x64-windows --compiler llvm --cmake true --ninja true --ccache true --vcpkg true"
                                    powershell "RefreshEnv.cmd"
                                }
                            }
                            script {
                                // Configure CMake
                                sh "cmake -S . -B ./build -G \"${env.GENERATOR}\" -D${env.PROJECT_NAME}_ENABLE_IPO=${env.ENABLE_IPO} -DCMAKE_BUILD_TYPE:STRING=${env.BUILD_TYPE} -D${env.PROJECT_NAME}_PACKAGING_MAINTAINER_MODE:BOOL=${env.PACKAGING_MAINTAINER_MODE} -D${env.PROJECT_NAME}_ENABLE_COVERAGE:BOOL=${env.BUILD_TYPE == 'Debug'}"
                            }
                            script {
                                // Build
                                sh "cmake --build ./build --config ${env.BUILD_TYPE}"
                            }
                        }
                    }
                }
            }
        }
    }
}