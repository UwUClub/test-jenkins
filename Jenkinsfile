pipeline {
    agent none
    stages {
        stage('build and test') {
            matrix {
                axes {
                    axis {
                        name 'PLATFORM'
                        values 'linux', 'windows'
                    }
                }
                stages {
                    stage('build') {
                        agent {
                            dockerfile {
                                filename "${PLATFORM == 'linux' ? 'DockerfileLinux' : 'DockerfileWindows'}"
                            }
                        }
                        steps {
                            script {
                                if (PLATFORM == 'linux') {
                                    sh 'cmake -S . -B build'
                                    sh 'cmake --build build --config Release -j 8'
                                } else {
                                    bat '.\\build.bat'
                                }
                            }
                        }
                    }
                    stage('test') {
                        agent {
                            dockerfile {
                                filename "${PLATFORM == 'linux' ? 'DockerfileLinux' : 'DockerfileWindows'}"
                            }
                        }
                        steps {
                            script {
                                if (PLATFORM == 'linux') {
                                    sh './build/proj'
                                } else {
                                    bat '.\\build\\Release\\proj.exe'
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
