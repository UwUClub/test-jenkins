pipeline {
    stages {
        agent {
            dockerfile {
                filename 'Dockerfile'
            }
        }
        stage('build') {
            steps {
                sh 'cmake -S . -B build'
                sh 'cmake --build build'
            }
        }
        stage('test') {
            steps {
                sh './build/proj'
            }
        }
    }
    stages {
        agent {
            dockerfile {
                filename 'DockerfileWindows'
            }
        }
        stage('build') {
            steps {
                sh 'cmake -S . -B build'
                sh 'cmake --build build'
            }
        }
        stage('test') {
            steps {
                sh './build/proj'
            }
        }
    }
}