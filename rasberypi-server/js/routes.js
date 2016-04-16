angular.module('app.routes', [])

.config(function($stateProvider, $urlRouterProvider) {

  // Ionic uses AngularUI Router which uses the concept of states
  // Learn more here: https://github.com/angular-ui/ui-router
  // Set up the various states which the app can be in.
  // Each state's controller can be found in controllers.js
  $stateProvider
    
  

      .state('ozoneRGBModes.ozoneRGBColor', {
    url: '/color',
    views: {
      'side-menu21': {
        templateUrl: 'templates/ozoneRGBColor.html',
        controller: 'ozoneRGBColorCtrl'
      }
    }
  })

  .state('ozoneRGBModes.ozoneRGBAnimation', {
    url: '/animation',
    views: {
      'side-menu21': {
        templateUrl: 'templates/ozoneRGBAnimation.html',
        controller: 'ozoneRGBAnimationCtrl'
      }
    }
  })

  .state('ozoneRGBParty', {
    url: '/party',
    templateUrl: 'templates/ozoneRGBParty.html',
    controller: 'ozoneRGBPartyCtrl'
  })

  .state('ozoneRGBAmbiLight', {
    url: '/page5',
    templateUrl: 'templates/ozoneRGBAmbiLight.html',
    controller: 'ozoneRGBAmbiLightCtrl'
  })

  .state('ozoneRGBModes', {
    url: '/side-menu21',
    templateUrl: 'templates/ozoneRGBModes.html',
    abstract:true
  })

$urlRouterProvider.otherwise('/side-menu21/color')

  

});