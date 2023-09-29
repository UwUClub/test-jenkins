pipeline {
    agent any

    stages {
        stage('build') {
            steps {
                sh 'who am i'
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