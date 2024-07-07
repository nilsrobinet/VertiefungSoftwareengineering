pipeline {
    triggers { pollSCM('H */4 * * *') }
    agent {
        dockerfile {
            filename 'Dockerfile'
            dir '.'
        }
    }
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                sh './build_scripts/makeC.sh'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
                ctest
                    installation: 'InSearchPath' 
                    arguments: '''
                --test-dir build/Release/test/
                ''' 
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
        changed {
            archiveArtifacts artifacts: 'build/docu/**/*.pdf', onlyIfSuccessful: true
        }
    }
}
