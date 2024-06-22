pipeline {
    triggers { pollSCM('H */4 * * *') }
    agent {
        docker { dockerfile true}
    }

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Docu') {
            steps {
                echo 'Building Documentation...'
                sh './build_scripts/makedoc.sh'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
    post {
        allways {
            archiveArtifacts artifacts: 'build/docu/**/*.pdf', onlyIfSuccessful: true
        }
    }
}
