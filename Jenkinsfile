pipeline {
    agent {
        docker {
            image 'ubuntu:latest'
        }
    }

    stages {
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