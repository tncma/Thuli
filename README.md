Thuli
=====

What is it?
-----------

We think of Thuli as an issue tracker for the Government!

A *thuli* need not merely be just a complaint/an issue/grievance but much more. It could be a proposal or simply an idea. By having a fluid, transparent, communication channel between the government and the people with incentives to sustain user interest and opportunities to take ownership, we believe this app is well poised to boost citizen engagement levels.

In Thamizh, a *thuli* means a drop. Just like how a drop of water serves as an adequate block to build an ocean from the bottom-up, we hope the *thulis* on the platform can both up the efficiency of urban governance and spur social consciousness among our younger citizens in a big way.

This project began as an idea for the two-day Tamil Nadu CMA *Code for Urban Governance* Hackathon 2013.

Demo
----

http://thulidev.devcloud.acquia-sites.com/

Technology
----------

- **Web**

  The web component of the application runs off the latest version of Drupal 7!
  
  Drupal is a good fit for this web app because it is both enough of a web framework to build on easily and has several components (either core or contributed) that add a lot of relevant features out of the box. Besides, it is multi-role capable, has a flexible permissions and access control system and is configuration-rich which is quite handy for the administrative component. It also helps that the software is open-source, highly popular and is backed by an excellent community.

- **Mobile**

  Stub

Installation
------------

- **Web**:

  As our application runs on Drupal, this means that you'd need to have the LAMP stack installed for you to get started. If you'd like, you are free to go for an [alternative web server](http://wiki.nginx.org/Drupal) or [SQL backend](https://drupal.org/module-categories/database-drivers). You can check the standard requirements for running Drupal [here](https://drupal.org/requirements).

  Once you've got that out of the way, I'd highly recommend [installing](http://drush.ws) `drush` before you continue. Drush is the Drupal CLI.

  Then, clone this repo to the document root of your web server (or that of your virtual host). Or clone elsewhere, and copy just the `web/` directory.

  Thuli is a Drupal installation profile by itself. So, if you'd be installing the site from the UI, you can just choose the profile as *Thuli* in the first page and then proceed as you would [normally install any other Drupal site](https://drupal.org/documentation/install/beginners).

  If you are using `drush`, you can execute the following command and you'll be done!

      drush si thuli 
        --db-url="mysql://dbuser:dbpass@dbhost/dbname"
        --account-name="admin"
        --account-pass="admin"
        --site-name="Thuli"
        --verbose

  Navigate to the URL of the site and login with the username `admin` and password `admin`.

- **Mobile**

  Stub

API
---

There is a REST API that allows programatically performing several key actions on the site. While the initial intent was to use it from the mobile app, there is also the potential to build related applications using it. The API uses HTTP Basic Authentication.

You can inspect the service endpoints and try out the API by importing [this collection](https://www.getpostman.com/collections/608629715bac0be5ac21) into the [Postman Chrome extension](https://chrome.google.com/webstore/detail/postman-rest-client/fdmmgilgnpjigdojojpjoooidkmcomcm?hl=en).

Remember to change the base URL if you'd like to use your own local installation of Thuli.

Features under development
--------------------------
- Points, Leaderboard and Offers (to incentivize citizens & sustain their interest)
- Allows citizens to take ownership of *Thulis* themselves. Allows organizations to place micro-bids.
- Allows posting anonymously and for officials and the poster to have a private comment stream.
- Allows officials to configure rules around managing Thulis & adding more custom attributes to individual thulis as their need may be (eg. Ward)

Features in our Wishlist
------------------------
- Geotagging the posted *Thuli* automatically by the user's location (when using the mobile app)
- Push notifications for every change of state of a *Thuli* to all stakeholders (poster, people who voted up, government officials)
- Delegated authentication using the e-version of Aadar ID, maybe
- Analytics:
  - Average *Thuli* resolution time
  - Leaderboard among municipalities on different parameters: Resolution time, First response time to a *Thuli* with sufficient vote ups.