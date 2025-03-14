const path = require("path");
const fs = require("fs");

const VERSION_IDENTIFIERS = ["noir", "aztec", "aztec_short"];

let versions;
async function getVersions() {
  if (!versions) {
    try {
      const aztecVersionPath = path.resolve(
        __dirname,
        "../../../.release-please-manifest.json"
      );
      const aztecVersion = JSON.parse(
        fs.readFileSync(aztecVersionPath).toString()
      )["."];
      versions = {
        aztec: `v${aztecVersion}`,
        aztec_short: aztecVersion,
      };
    } catch (err) {
      throw new Error(
        `Error loading versions in docusaurus preprocess step.\n${err}`
      );
    }
  }
  return versions;
}

async function preprocessIncludeVersion(markdownContent) {
  const originalContent = markdownContent;
  for (const identifier of VERSION_IDENTIFIERS) {
    const version = (await getVersions())[identifier];
    markdownContent = markdownContent.replaceAll(
      `#include_${identifier}_version`,
      version
    );
  }
  return {
    content: markdownContent,
    isUpdated: originalContent !== markdownContent,
  };
}

module.exports = { preprocessIncludeVersion };
