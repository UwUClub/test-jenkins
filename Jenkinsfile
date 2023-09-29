pipeline {
    agent any

    stages {
        stage('build') {
            steps {
                sh 'whoami'
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