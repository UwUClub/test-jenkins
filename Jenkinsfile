pipeline {
    agent {
        dockerfile true
    }

    stages {
        stage('build') {
            steps {
                sh 'apt install -y build-essential'
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