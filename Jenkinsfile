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
                ctest arguments: '''
                --test-dir build/Release/test/
                ''', installation: 'InSearchPath'
            }
        }
        stage('Docu') {
            steps {
                echo 'Building Documentation...'
                sh './build_scripts/makedoc.sh'
            }
        }
        stage('Deploy') {
            when {
                expression {
                    env.BRANCH_NAME == 'main'
                }
            }
            steps {
                echo 'Deploying....'
                sh './build_scripts/deploy.sh'
            }
        }
    }
    post {
        always {
            junit 'build/test/ctest.junit.xml'
            archiveArtifacts artifacts: 'build/docu/**/*.pdf', onlyIfSuccessful: true
        }
    }
}
